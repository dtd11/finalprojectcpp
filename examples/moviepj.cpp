#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <numeric>
#include "openai.hpp"

class MovieLogger {
private:
    std::string userName;
    std::string fileName;

    const std::vector<std::string> genres = {
        "Action", "Drama", "Comedy", "Romance", "Thriller", "Family", "Animation", "Fantasy", "Science Fantasy", "Horror", "Crime", "Adventure", "Musical", "Documentary"};

public:
    MovieLogger(const std::string& name) : userName(name), fileName(name + "_movies.txt") {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::ofstream newFile(fileName);
            newFile.close();
        }
    }

    void displayGenres() const {
        std::cout << std::left;
        std::cout << "-------------------------------------------------------------------------------------------\n";
        std::cout << "|                                         Genre                                           |\n";
        std::cout << "-------------------------------------------------------------------------------------------\n";

        int count = 1;
        for (size_t i = 0; i < genres.size(); ++i) {
            std::cout << "| " << std::setw(2) << count++ << " | " << std::setw(24) << genres[i] << " ";

            if (count % 3 == 1) {
                std::cout << "|\n";
                std::cout << "-------------------------------------------------------------------------------------------\n";
            }
        }
        std::cout << std::endl;
    }

    void addMovieEntry() {
        std::ofstream file(fileName, std::ios::app);

        if (file.is_open()) {
            std::string date, title, mood;
            size_t genreIndex;
            std::string genre;

            std::cout << "Enter the date (YYYY-MM-DD): ";
            std::cin >> date;

            std::cout << "Enter the movie title: ";
            std::cin.ignore();
            std::getline(std::cin, title);

            displayGenres();
            std::cout << "Choose the movie genre (enter the number): ";
            std::cin >> genreIndex;

            if (genreIndex < 1 || genreIndex > static_cast<std::size_t>(genres.size())) {
                std::cerr << "Invalid genre index. Please enter again." << std::endl;
                return;
            }

            genre = genres[genreIndex - 1];

            std::cout << "Enter your mood at that time (from 0 to 5, 0: Terrible, 1: Bad, 2: Okay, 3: Good, 4: Great, 5: Excellent): ";
            std::cin >> mood;

            if (std::stoi(mood) < 0 || std::stoi(mood) > 5) {
                std::cerr << "Invalid mood value. Please enter a value from 0 to 5." << std::endl;
                return;
            }

            file << date << ", " << title << ", " << genre << ", " << mood << ", " << genreIndex - 1 << std::endl;
            std::cout << "The movie has been successfully added." << std::endl;

            file.close();
        }
        else {
            std::cerr << "Unable to open the file." << std::endl;
        }
    }

    void recommendMovie() {
        std::cout << "Enter your current mood (from 0 to 5): ";
        const int arraySize = 14;
        int currentMood;
        std::cin >> currentMood;

        std::ifstream file(fileName);
        std::vector<double> moodValues;
        std::vector<int> genreValues;
        double movieGenresWeight[arraySize];
        for (int i = 0; i < arraySize; ++i)
        {
            movieGenresWeight[i] = 0.0;
        }

        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                std::istringstream iss(line);
                std::string date, title, genre, moodStr, genreIndex;
                getline(iss, date, ',');
                getline(iss, title, ',');
                getline(iss, genre, ',');
                getline(iss, moodStr, ',');
                getline(iss, genreIndex);
                
                int savedMood = std::stoi(moodStr);
                moodValues.push_back(savedMood);
                size_t savedGenre = std::stoi(genreIndex);
                genreValues.push_back(savedGenre);
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open the file." << std::endl;
            return;
        }

        double maxCosineSimilarity = -1.0;
        double maxPearsonCorrelation = -1.0;
        std::string recommendedGenreCosine;
        std::string recommendedGenrePearson;

        for (size_t i = 0; i < static_cast<std::size_t>(genres.size()); ++i) {
            double cosineSimilarityValue = calculateCosineSimilarity(moodValues, currentMood, i, genreValues);
            double pearsonCorrelationValue = calculatePearsonCorrelation(moodValues, currentMood, i, genreValues);
            std::cout << std::left;
            std::cout << genres[i] << "와 현재 기분에 대한 상관계수 " <<  " Cosine " << cosineSimilarityValue <<  " Pearson " << pearsonCorrelationValue << std::endl;
            if (cosineSimilarityValue > pearsonCorrelationValue){
                movieGenresWeight[i] = cosineSimilarityValue;
            }
            else {
                movieGenresWeight[i] = pearsonCorrelationValue;
            }
            
            if (cosineSimilarityValue > maxCosineSimilarity) {
                maxCosineSimilarity = cosineSimilarityValue;
                recommendedGenreCosine = genres[i];
            }

            if (pearsonCorrelationValue > maxPearsonCorrelation) {
                maxPearsonCorrelation = pearsonCorrelationValue;
                recommendedGenrePearson = genres[i];
            }
        }
        std::string final_genre = (maxCosineSimilarity > maxPearsonCorrelation) ? recommendedGenreCosine : recommendedGenrePearson;
        std::cout << "-------------------------------------------------------------------------------------------\n";
        std::cout << "My recommended movie genre is " << final_genre << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------\n";
        
        std::string text = "Recommend 5 movies  in the order of the highest genre weights , where ";

        for (size_t i = 0; i < genres.size(); ++i)
        {
            std::string strNum = std::to_string(movieGenresWeight[i]);
            text = text + genres[i] + " has a weight of " + strNum + ". ";
        }
        std::cout << text << std::endl;
        
        openai::start();
        nlohmann::json payload = {
        {"model", "text-davinci-003"},
        {"prompt", text},
        {"max_tokens", 500},
        {"temperature", 0.7}
    	};
        auto completion = openai::completion().create(payload);
    	std::string str = completion["choices"][0]["text"].get<std::string>();
    	str.substr(2);
    	std::cout << "Recommend Movie Lists: " << str << "\n" << std::endl;
        
        

    }

private:
     double calculateCosineSimilarity(const std::vector<double>& moodValues, int currentMood, int genreIndex, const std::vector<int>& genreValues) const {
        double dotProduct = 0.0;
        double normMoodValues = 0.0;
        double normCurrentMood = 0.0;
        double PI = 3.141592;
        for (size_t i = 0; i < moodValues.size(); ++i) {
            double genreWeight = (genreIndex == genreValues[i]) ? cos(PI * (currentMood - moodValues[i]) / 5) : 0;
            dotProduct += genreWeight;
            normMoodValues += pow((genreIndex == genreValues[i]) ? 1 : 0, 2);
            normCurrentMood += pow((genreIndex == genreValues[i]) ? 1 : 0, 2);
        }
        
        if (normMoodValues == 0 || normCurrentMood == 0) {
            return 0.0; 
        }
        double similarity = dotProduct / (sqrt(normMoodValues) * sqrt(normCurrentMood));
        return similarity;
    }

    double calculatePearsonCorrelation(const std::vector<double>& moodValues, int currentMood, int genreIndex, const std::vector<int>& genreValues) const {
        size_t n = moodValues.size();
        double PI = 3.141592;
        double meanMoodValues = std::accumulate(moodValues.begin(), moodValues.end(), 0.0) / n;
        double meanCurrentMood = (static_cast<std::size_t>(genreIndex) < n) ? moodValues[genreIndex] : currentMood;

        double numerator = 0.0;
        double denomMoodValues = 0.0;
        double denomCurrentMood = 0.0;

        for (size_t i = 0; i < n; ++i) {
            double genreWeight = (genreIndex == genreValues[i]) ? cos(PI * (currentMood - moodValues[i]) / 5) : 0;
            numerator += (moodValues[i] - meanMoodValues) * genreWeight;
            denomMoodValues += pow((genreIndex == genreValues[i]) ? moodValues[i] - meanMoodValues : 0, 2);
            denomCurrentMood += pow((genreIndex == genreValues[i]) ? currentMood - meanCurrentMood : 0, 2);
        }
        if (denomMoodValues == 0 || denomCurrentMood == 0) {
            return 0.0;
        }
        double correlation = numerator / (sqrt(denomMoodValues) * sqrt(denomCurrentMood));
        return correlation;
    }

public:
    void startProgram() {
        int mode;
        do {
            std::cout << "1. Movie Add Mode\n";
            std::cout << "2. Movie Recommendation Mode\n";
            std::cout << "0. Exit Program\n";
            std::cout << "Choose the mode: ";
            std::cin >> mode;

            switch (mode) {
            case 1:
                addMovieEntry();
                break;
            case 2:
                recommendMovie();
                break;
            case 0:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid input. Please choose again.\n";
            }
        } while (mode != 0);
    }
};

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    MovieLogger movieLogger(name);
    movieLogger.startProgram();

    return 0;
}
