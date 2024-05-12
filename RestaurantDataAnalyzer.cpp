#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

const string DATA_FILE = "RestaurantData.txt";
const string OUTPUT_FILE_A = "OutputA.txt";
const string OUTPUT_FILE_B = "OutputB.txt";

void readDataFromFile(vector<int>& status, vector<int>& method, vector<int>& foodRating, vector<int>& priceRating, vector<int>& serviceRating) {
    ifstream data(DATA_FILE);
    if (!data.is_open()) {
        cerr << "Error: Unable to open file: " << DATA_FILE << endl;
        exit(EXIT_FAILURE);
    }

    int data1, data2, data3, data4, data5;
    while (data >> data1 >> data2 >> data3 >> data4 >> data5) {
        status.push_back(data1);
        method.push_back(data2);
        foodRating.push_back(data3);
        priceRating.push_back(data4);
        serviceRating.push_back(data5);
    }
    data.close();
}

void displayMaxRatingByStatus(const vector<int>& status, const vector<int>& priceRating) {
    ofstream outFile(OUTPUT_FILE_A);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file: " << OUTPUT_FILE_A << endl;
        exit(EXIT_FAILURE);
    }

    int max0 = 1, max1 = 1, max2 = 1, max3 = 1;

    for (size_t i = 0; i < status.size(); i++) {
        if (status[i] == 0 && priceRating[i] > max0) {
            max0 = priceRating[i];
        } else if (status[i] == 1 && priceRating[i] > max1) {
            max1 = priceRating[i];
        } else if (status[i] == 2 && priceRating[i] > max2) {
            max2 = priceRating[i];
        } else if (status[i] == 3 && priceRating[i] > max3) {
            max3 = priceRating[i];
        }
    }

    cout << "Fast Food " << max0 << endl
         << "Casual Dining " << max1 << endl
         << "Fine Dining " << max2 << endl
         << "Cafe " << max3 << endl;

    outFile << "Fast Food " << max0 << endl
            << "Casual Dining " << max1 << endl
            << "Fine Dining " << max2 << endl
            << "Cafe " << max3 << endl;

    outFile.close();
}

void displayAvgRatingByMethod(const vector<int>& method, const vector<int>& serviceRating) {
    ofstream outFile(OUTPUT_FILE_B);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file: " << OUTPUT_FILE_B << endl;
        exit(EXIT_FAILURE);
    }

    const int METHOD_COUNT = 5;
    vector<double> total(METHOD_COUNT, 0);
    vector<int> count(METHOD_COUNT, 0);
    vector<double> avg(METHOD_COUNT, 0);

    for (size_t i = 0; i < method.size(); i++) {
        int methodIndex = method[i];
        total[methodIndex] += serviceRating[i];
        count[methodIndex]++;
    }

    for (int i = 0; i < METHOD_COUNT; i++) {
        avg[i] = count[i] == 0 ? 0 : total[i] / count[i];
    }

    const string METHOD_NAMES[] = {"Drive-thru", "Counter Service", "Sit-down", "Takeaway", "Delivery"};

    for (int i = 0; i < METHOD_COUNT; i++) {
        cout << fixed << setprecision(2) << METHOD_NAMES[i] << " " << avg[i] << endl;
        outFile << fixed << setprecision(2) << METHOD_NAMES[i] << " " << avg[i] << endl;
    }

    outFile.close();
}

int main() {
    vector<int> status;
    vector<int> method;
    vector<int> foodRating;
    vector<int> priceRating;
    vector<int> serviceRating;
    char choice;

    cout << "Restaurant Data in Tallahassee" << endl
         << "Options" << endl
         << "A) Display the maximum Price Rating by Restaurant Type..." << endl
         << "B) Display the average Service Rating by Service Method..." << endl
         << "Please select option (A-B)..." << endl;

    cin >> choice;

    while (choice != 'A' && choice != 'a' && choice != 'B' && choice != 'b') {
        cout << "Invalid option entered" << endl
             << "Please select option (A-B)..." << endl;
        cin >> choice;
    }

    readDataFromFile(status, method, foodRating, priceRating, serviceRating);

    switch (choice) {
        case 'A':
        case 'a':
            displayMaxRatingByStatus(status, priceRating);
            break;
        case 'B':
        case 'b':
            displayAvgRatingByMethod(method, serviceRating);
            break;
    }

    return 0;
}
