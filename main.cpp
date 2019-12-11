#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct teacher {
    string firstName;
    string lastName;
    string classSubject;
    int studentCount;
};

struct pupil {
    string firstName;
    string lastName;
    string classSubject;
    string grade;
    int teacherId;
};


void readTeachers(teacher Teachers[], int teacherCount, const char filename[]);
void readPupils(pupil Pupils[], int pupilCount, const char filename[]);
void assignTeacherId(teacher Teachers[], int teacherCount, pupil Pupils[], int pupilCount);
void countPupils(teacher Teachers[], int teacherCount, pupil Pupils[], int pupilCount);
int findLineCount(const char filename[]);

int main() {
    const char teachers[] = "mokytojai.txt",
               pupils[] = "mokiniai.txt";
    int teacherCount = findLineCount(teachers),
        pupilCount = findLineCount(pupils);
    teacher Teachers[teacherCount];
    pupil Pupils[pupilCount];

    readTeachers(Teachers, teacherCount, teachers);
    readPupils(Pupils, pupilCount, pupils);

    assignTeacherId(Teachers, teacherCount, Pupils, pupilCount);
    countPupils(Teachers, teacherCount, Pupils, pupilCount);

//    for(int i = 0; i < teacherCount; i++) {
//        cout << Teachers[i].firstName << " " << Teachers[i].lastName << " " << Teachers[i].classSubject << " " << Teachers[i].studentCount;
//        cout << '\n';
//    }
//    cout << '\n';
//    for(int i = 0; i < pupilCount; i++) {
//        cout << Pupils[i].firstName << " " << Pupils[i].lastName << " " << Pupils[i].classSubject << " " << Pupils[i].grade << " " << Pupils[i].teacherId;
//        cout << '\n';
//    }

    return 0;
}

void readTeachers(teacher Teachers[], int teacherCount, const char filename[])
{
    ifstream in(filename);

    for(int i = 0; i < teacherCount; i++) {
        in >> Teachers[i].firstName >> Teachers[i].lastName >> Teachers[i].classSubject;
        Teachers[i].studentCount = 0;
    }

    in.close();
}

void readPupils(pupil Pupils[], int pupilCount, const char filename[])
{
    ifstream in(filename);

    for(int i = 0; i < pupilCount; i++) {
        in >> Pupils[i].firstName >> Pupils[i].lastName >> Pupils[i].classSubject >> Pupils[i].grade;
    }

    in.close();
}

int findLineCount(const char filename[])
{
    ifstream in(filename);
    int n = 0;
    string line;

    while(!in.eof()) {
        getline(in, line);
        n++;
    }
    in.close();

    return n;
}

void assignTeacherId(teacher Teachers[], int teacherCount, pupil Pupils[], int pupilCount)
{
    for (int i = 0; i < pupilCount; i++) {
        for (int j = 0; j < teacherCount; j++) {
            if (Pupils[i].classSubject == Teachers[j].classSubject) {
                Pupils[i].teacherId = j++;
            }
        }
    }
}

void countPupils(teacher Teachers[], int teacherCount, pupil Pupils[], int pupilCount)
{
    for (int i = 1; i <= pupilCount; i++) {
        for (int j = 0; j < teacherCount; j++) {
            if(Pupils[i].teacherId == j) {
                Teachers[j].studentCount++;
            }
        }

    }

}

// TODO Isvesti dar mokytojus, kuriu mokiniu vidurkis yra mazesnis, nei bendras vidurkis
// mokytojo id mokiniu strukturoje