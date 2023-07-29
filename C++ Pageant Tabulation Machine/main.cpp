#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>


using namespace std;


const int maxNumcandi = 100, maxNumcrit = 10;

struct Criterion {
    string name;
    double percentage;
};

struct Candidate {
    string name;
    double scores[maxNumcrit];
    double overallScore;
    int rankC;
};


double getValidPercentage() {
    double percentage;
    do {
        cout << "Enter percentage: ";
        cin >> percentage;
        if (percentage < 0.0 || percentage > 100.0) {
            cout << "Invalid percentage. Please enter a value between 0 and 100.\n";
        }

    } while (percentage < 0.0 || percentage > 100.0);

    return percentage;
}



void enterCandidateNames(int numCandidates, Candidate candidates[]) {
    for (int i = 0; i < numCandidates; ++i) {
        cout << "Enter name for Candidate " << i + 1 << ": ";
        getline(cin, candidates[i].name);
    }
    cout << "---------------------------------------------------------" << endl;
}


double entCritera(int numCriteria, Criterion criteria[]) {
    double totalcrit = 0.0;
    do {
        totalcrit = 0.0;
        for (int i = 0; i < numCriteria; ++i) {
            cout << "Enter name for Criterion " << i + 1 << ": ";
            cin.ignore();
            getline(cin, criteria[i].name);
            criteria[i].percentage = getValidPercentage();
            totalcrit += criteria[i].percentage;
        }
        if (totalcrit != 100.0) {
            cout << "Criteria must have a total of 100%. Please try again!" << endl;
            cout << endl;
        }
    } while (totalcrit != 100.0);
    cout << "---------------------------------------------------------" << endl;


    return totalcrit;
}

bool compareCandidates(const Candidate& candidate1, const Candidate& candidate2) {
    return candidate1.overallScore > candidate2.overallScore;
}

void printCandidateSummary(ofstream& outFile, int numCandidates, Criterion criteria[], int numCriteria, Candidate candidates[]) {
    outFile << "Number of Candidates: " << numCandidates << endl;
    outFile << "Number of Criteria: " << numCriteria << endl;
    outFile << "Summary of Criteria and their Percentage:" << endl;

    outFile << setw(15) << left << "Criterion" << setw(15) << left << "Percentage" << endl;
    for (int ab = 0; ab < numCriteria; ab++)
    {
        outFile << setw(4) << left << " " << setw(15) << left << criteria[ab].name << setw(15) << left << criteria[ab].percentage << endl;
    }

    for (int i = 0; i < numCandidates; ++i)
    {
        candidates[i].rankC = i + 1;
    }
    outFile << endl;
    outFile << "Ranking" << endl;

    for (int i = 0; i < numCandidates; ++i)
    {
        if (i == 0)
        {
            outFile << "1st Runner Up: " << candidates[i].name << " with overall score " << candidates[i].overallScore << endl;
        }
        else if (i == 1)
        {
            outFile << "2nd Runner Up: " << candidates[i].name << " with overall score " << candidates[i].overallScore << endl;
        }
        else if (i == 2)
        {
            outFile << "3rd Runner Up: " << candidates[i].name << " with overall score " << candidates[i].overallScore << endl;
        }
        else
        {
            outFile << i + 1 << "th Runner Up: " << candidates[i].name << " with overall score " << candidates[i].overallScore << endl;
        }

    }
    outFile << "====================================================" << endl;
}



void homePage() {
    cout << "====================<< Tabulation Machine >>====================" << endl;
    cout << "||                                                            ||" << endl;
    cout << "||              Welcome to Tabulation Machine!                ||" << endl;
    cout << "================================================================" << endl;
    cout << endl;
    cout << "          --< Please set your Machine before all! >--" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "1) Set Machine" << endl;
    cout << "2) Start Scoring" << endl;
    cout << "3) View Result" << endl;
    cout << "4) Exit" << endl;
    cout << endl;
    cout << "Choose: ";
}

int main() {
    int ans;
    char ansL;
    int numCandidates, numCriteria;
    Criterion criteria[maxNumcrit];
    Candidate candidates[maxNumcandi];
    bool isMachineset = false;
    bool isResultready = false;

    do{

    homePage();
    cin >> ans;
    cin.ignore();
    system("cls");
    switch(ans)
    {
        case 1:
        {
                if (isMachineset == false)
                {

                    cout << "====================================" << endl;
                    cout << "|| Great! let's set your machine! ||" << endl;
                    cout << "====================================" << endl;
                    cout << endl;
                    cout << "Enter the number of candidates: ";
                    cin >> numCandidates;
                    cin.ignore();
                    enterCandidateNames(numCandidates, candidates);


                    cout << endl;
                    cout << "Enter the number of criteria: ";
                    cin >> numCriteria;
                    cout << "Note: Criteria must have a total of 100%!\n" << endl;
                    entCritera(numCriteria, criteria);


                    cout << endl;
                    cout << "You have set your Machine. Here is the summary." << endl;
                    cout << endl;
                    cout << setw(4) << left << " " << setw(15) << left << "Criteria" << setw(15) << left << "Percentage" << setw(10) << left << "Score" << endl;
                    cout << endl;
                    for (int ab = 0; ab < numCriteria; ab++)
                        {
                            cout << setw(4) << left << " " << setw(15) << left << criteria[ab].name << setw(15) << left << criteria[ab].percentage << setw(10) << left << "To follow" << endl;
                            cout << endl;
                        }
                    isMachineset = true;
                    system("pause");
                    system("cls");
                    break;
                }
                else
                {
                    cout << "======================================" << endl;
                    cout << "|| You already set up your machine! ||" << endl;
                    cout << "======================================\n" << endl;
                    system("pause");
                    system("cls");
                    break;
                }

        }
         case 2:
            {
                if (isMachineset == true)
                {
                    cout << "============================================" << endl;
                    cout << "|| Awesome! You may enter your score now! ||" << endl;
                    cout << "============================================" << endl;

                    //to get scores for each candidate on each criterion
                    for (int sr = 0; sr < numCandidates; sr++) {
                        cout << "Enter Score for " << candidates[sr].name << endl;
                        for (int sc = 0; sc < numCriteria; sc++) {
                            double score = 0;
                            cout << "Score for " << criteria[sc].name << " : ";
                            cin >> score;
                            candidates[sr].scores[sc] = score;
                        }
                        cout << "----------" << endl;
                        cout << endl;
                    }

                    system("Pause");
                    system("cls");
                    isResultready = true;
                    break;
                }
                else
                {
                    cout << "=======================================================" << endl;
                    cout << "|| You haven't set your machine. Can't enter scores! ||" << endl;
                    cout << "=======================================================\n" << endl;

                    system("Pause");
                    system("cls");
                    break;
                }
            }

            case 3:
            {
                if (isResultready == true)
                {
                    cout << "===========================" << endl;
                    cout << "|| Here are the results! ||" << endl;
                    cout << "===========================" << endl;
                    cout << endl;
                    cout << endl;
                    // compute overall scores for each candidate
                    cout << setw(4) << left << " " << setw(30) << left << "Name" << setw(25) << left << "Overall Score" << endl;
                    for (int i = 0; i < numCandidates; ++i)
                    {
                        double overAllscore = 0;
                        for (int cs = 0; cs < numCriteria; cs++)
                        {
                            overAllscore += (candidates[i].scores[cs] * (criteria[cs].percentage / 100.0));
                        }
                        candidates[i].overallScore = overAllscore;
                        cout << endl;
                        cout << setw(4) << left << " " << setw(30) << left << candidates[i].name << setw(25) << left << candidates[i].overallScore <<setw(10) << endl;

                    }


                    cout << endl;
                    sort(candidates, candidates + numCandidates, compareCandidates);
                    for (int i = 0; i < numCandidates; ++i) {
                        candidates[i].rankC = i + 1;
                    }

                    cout << "--< Ranking >--" << endl;

                    for (int i = 0; i < numCandidates; ++i) {
                        if (i == 0) {
                            cout << "1st Runner Up: " << candidates[i].name << " with overall score of " << candidates[i].overallScore << "%" << endl;
                        } else if (i == 1) {
                            cout << "2nd Runner Up: " << candidates[i].name << " with overall score of " << candidates[i].overallScore << "%" << endl;
                        } else if (i == 2) {
                            cout << "3rd Runner Up: " << candidates[i].name << " with overall score of " << candidates[i].overallScore << "%" << endl;
                        } else {
                            cout << i + 1 << "th Runner Up: " << candidates[i].name << " with overall score of " << candidates[i].overallScore << "%" << endl;
                        }
                    }
                    system("Pause");
                    system("cls");
                    break;
                }
                else
                {
                    cout << "===========================================================" << endl;
                    cout << "|| You haven't entered your score, Result can't display! ||" << endl;
                    cout << "===========================================================\n" << endl;

                    system("Pause");
                    system("cls");
                    break;
                }
            }
        case 4:
        {
             cout << "=================================================" << endl;
             cout << "|| Existing Machine...Thank you for using!...  ||" << endl;
             cout << "=================================================" << endl;
             break;
        }
        default:
        {
            cout << "Invalid choice. Please try again!" << endl;
            system("pause");
            system("cls");
        }

        }
    }while(ans != 4);

    ofstream outFile;
    outFile.open("tabulation_result.txt", ios::app);
    if (outFile.is_open())
        {
            if (isResultready == true)
            {
            printCandidateSummary(outFile, numCandidates, criteria, numCriteria, candidates);
            outFile.close();
            }
        }

    else {
        cout << "Error: Unable to open the output file." << endl;
    }


    return 0;
}
