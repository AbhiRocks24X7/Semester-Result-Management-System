#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <iostream> 
#include <complex>
#include <queue>
#include <set>
#include <unordered_set>
#include <list>
#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <iomanip>
#include <fstream>
 
using namespace std;
 
typedef long long ll;

ll MOD = 998244353;

double eps = 1e-12;

#define ln "\n"

#define INF 2e18

//function to take fast inputs
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)




class CGPA {
private:

    vector<vector<double>> semesterSGPAs; // stores SGPAs after each semester

public:
    vector<int> marks; //stores the actual marks

    vector<int> credits; //stores the credits of subjects

    vector<int> highestMarks; //stores the highest marks to calculate relative

    vector<int> gradePoints; //stores the grades

    double sgpa; //sgpa of current sem

    vector<double> allSgpa; //stores all SGPA

    double cgpa; //cgpa

    vector<double> normalisedMarks; //normalised marks for relative grading

    //function to find relative marks
    double normalise(int highest, int marks) {

        double factor = 100.0 / (double) highest;

        return (double) marks * factor;
    }

    
    void storeNormalisedMarks() {

        normalisedMarks.clear();

        for(int i = 0; i < marks.size(); i++) {

            double normalisedMark = normalise(highestMarks[i], marks[i]);
            normalisedMarks.push_back(normalisedMark);
        }
    }

    //function to calculate grades
    int calculateGP(double normalisedMarks) {

        if(normalisedMarks >= 91) {

            return 10;
        } 
        else if(normalisedMarks >= 81 && normalisedMarks < 91) {

            return 9;
        } 
        else if(normalisedMarks >= 71 && normalisedMarks < 81) {

            return 8;
        } 
        else if(normalisedMarks >= 61 && normalisedMarks < 71) {

            return 7;
        } 
        else if(normalisedMarks >= 51 && normalisedMarks < 61) {

            return 6;
        } 
        else if(normalisedMarks >= 41 && normalisedMarks < 51) {

            return 5;
        } 
        else if(normalisedMarks >= 35 && normalisedMarks < 41) {

            return 4;
        } 
        else {

            return 0;
        }
    }

    void storeGP() {

        gradePoints.clear();

        for(double mark : normalisedMarks) {

            int gp = calculateGP(mark);
            gradePoints.push_back(gp);
        }
    }

    //function to calculate sgpa
    void calculateSGPA() {

        int totalGP = 0;

        for(int i = 0; i < gradePoints.size(); i++) {

            totalGP += gradePoints[i] * credits[i];
        }
        
        int totalCredits = accumulate(credits.begin(), credits.end(), 0);

        sgpa = (double)totalGP / (double) totalCredits;

        allSgpa.push_back(sgpa);
        semesterSGPAs.push_back(allSgpa);
    }

    //function to calculate cgpa
    void calculateCGPA() {

        double sum = accumulate(allSgpa.begin(), allSgpa.end(), 0.0);
        cgpa = sum / allSgpa.size();
    }

    //getter function to get all sgpa
    vector<vector<double>> getSemesterSGPAs() const {

        return semesterSGPAs;
    }
};

int main() {

    int numSemesters;

    cout << "Enter the number of semesters: ";
    cin >> numSemesters;

    CGPA student;

    for (int semester = 1; semester <= numSemesters; semester++) {

        cout << "Enter details for Semester " << semester << ":" << ln;

        int numSubjects;

        cout << "Enter the number of subjects for Semester " << semester << ": ";
        cin >> numSubjects;

        cout << "Enter marks, credits, and highest marks for each subject:" << ln;

        for (int i = 0; i < numSubjects; i++) {

            int marks, credits, highestMarks;

            cout << "Subject " << i + 1 << ": ";
            cin >> marks >> credits >> highestMarks;

            student.marks.push_back(marks);
            student.credits.push_back(credits);
            student.highestMarks.push_back(highestMarks);
        }

        // Calculate SGPA for the semester
        student.storeNormalisedMarks();

        student.storeGP();

        student.calculateSGPA();

        student.marks.clear();

        student.credits.clear();

        student.highestMarks.clear();

        student.normalisedMarks.clear();

        student.gradePoints.clear();
    }

    // Display SGPA for each semester
    cout << "\nSGPAs after each semester:" << ln;

    int semesterCount = 1;

    for (const auto &semesterSGPA : student.getSemesterSGPAs()) {

        cout << "Semester " << semesterCount++ << ": ";

        for (double sgpa : semesterSGPA) {
            cout << sgpa << " ";
        }
        cout << ln;
    }

    // Calculate and display CGPA
    student.calculateCGPA();
    
    cout << "\nOverall CGPA: " << student.cgpa << ln;

    return 0;
}