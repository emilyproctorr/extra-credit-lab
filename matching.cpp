#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// define all variables and arrays
int ranking_conflict[1][2]; // keep track of conflicts between departments
int depart_1; // department 1 that has conflict
int depart_2; // department 2 that has conflict
int department_choice[5]; // final results/decisions
int ranking;
int depart_rank[5][5]; // rankings for all departments 
int prog_rank[5][5]; // rankings for all programmers
int flag = 0; // flag for choices

// finds conflicts between departments
void find_conflicts(int ranking[])
{
    // for each department
    for (int i = 0; i < 5; ++i) {
        // no conflict
        flag = 0;
        // for all other departments (besides the one were on)
        for (int j = 0; j < 5; ++j) {
            // if we are comparing two different departemnts
            if (i != j) {
                // if they have the same ranking
                if (ranking[i] == ranking[j])
                {
                    // add the two departments that have a conflict
                    ranking_conflict[0][0] = i; 
                    ranking_conflict[0][1] = j;
                    flag = 1;
                    break;
                }
            }
        } if (flag == 1) {
            break;
        }
    }
}

void assign()
{
    for(int i = 0; i <= 5; ++i){
        // get conflicts between departments
        find_conflicts(depart_rank[0]);
        // if there are no conflicts
        if (ranking_conflict[0][0] == 0 && ranking_conflict[0][1] == 0) {
            break;
        } else {
            int current_programmer = depart_rank[0][ranking_conflict[0][0]];
            // assign the two departments with conflicts
            depart_1 = ranking_conflict[0][0];
            depart_2 = ranking_conflict[0][1];

            for (int j = 0; j < 5; ++j) {
                // if department 1 is higher on programmer rankings
                if (prog_rank[j][current_programmer] == depart_1) {
                    // assign current programmer to department 1
                    department_choice[depart_1] = current_programmer;
                    // change the ranking for the department 2
                    for (int n = 0; n < 5; ++n) {
                        depart_rank[n][depart_2] = depart_rank[n+1][depart_2];
                    } break;
                // if department 2 is higher on programmer rankings
                } else if (prog_rank[j][current_programmer] == depart_2) {
                    // assign current programmer to department 2
                    department_choice[depart_2] = current_programmer;
                    // change the ranking for the department 1
                    for (int n = 0; n < 5; ++n) {
                        depart_rank[n][depart_1] = depart_rank[n+1][depart_1];
                    } break;
                } else {
                    continue;
                }
            }

        }
    }

}

// gets arrays from input file for department and programmer rankings
void read_file(string filename)
{
    // read file
    ifstream input_file;
    input_file.open(filename);
    if(input_file.is_open()) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                input_file >> ranking;
                // do rankings - 1 to match indexes
                depart_rank[i][j] = ranking - 1;
            }
        }

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                input_file >> ranking;
                // do rankings - 1 to match indexes
                prog_rank[i][j] = ranking - 1;
            }
        }
    }
    input_file.close();
}

int main()
{
    read_file("matching-data.txt");
    assign();
    for (int i = 0; i < 5; ++i){
        department_choice[i]= depart_rank[0][i];
    }
    // print output
    for (int i = 0; i < 5; ++i) {
        cout << "Department #" << i + 1 << " will get Programmer # " << department_choice[i] + 1 << endl;
    }
    return 0;
}