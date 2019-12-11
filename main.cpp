#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

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
    int grade;
    int teacherId;
};


void readTeachers(teacher Teachers[], int teacherCount, const char filename[]);
void readPupils(pupil Pupils[], int pupilCount, const char filename[]);
void assignTeacherId(teacher Teachers[], int teacherCount, pupil Pupils[], int pupilCount);
void countPupils(teacher Teachers[], int teacherCount, pupil Pupils[], int pupilCount);
string getTeacherWithMostPupils(teacher Teachers[], int teacherCount);
string getTeacherWithTopPupils(teacher Teachers[], pupil Pupils[], int pupilCount);
int getAverageGrade(pupil Pupils[], int pupilCount);
int getWorstTeacherCount(teacher Teachers[], int teacherCount, pupil Pupils[], int pupilCount, int averageGrade);
void getTeachersWithWorstPupils(teacher Teachers[], pupil Pupils[], int pupilCount, int averageGrade, string worstTeachers[]);
void writeResults();
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

    string teacherWithMostPupils = getTeacherWithMostPupils(Teachers, teacherCount);
//    cout << teacherWithMostPupils;
    string teacherWithTopPupils = getTeacherWithTopPupils(Teachers, Pupils, pupilCount);
//    cout << '\n' << teacherWithTopPupils;
    int averagePupilGrade = getAverageGrade(Pupils, pupilCount);
//    cout << averagePupilGrade;

    int worstTeacherCount = getWorstTeacherCount(Teachers, teacherCount, Pupils, pupilCount, averagePupilGrade);
    string worstTeachers[worstTeacherCount];
    getTeachersWithWorstPupils(Teachers, Pupils, pupilCount, averagePupilGrade, worstTeachers);
    for(int i = 0; i < worstTeacherCount; i++) {
        cout << worstTeachers[i];
        cout << '\n';
    }

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
    for (int i = 0; i < pupilCount; i++) {
        for (int j = 0; j < teacherCount; j++) {
            if(Pupils[i].teacherId == j) {
                Teachers[j].studentCount++;
            }
        }

    }

}

string getTeacherWithMostPupils(teacher Teachers[], int teacherCount)
{
    string teacherWithMostPupils = " ";
    int pupilCount = 0;
    for(int i = 0; i < teacherCount - 1; i++) {
        if (Teachers[i].studentCount > pupilCount) {
            pupilCount = Teachers[i].studentCount;
            teacherWithMostPupils = Teachers[i].firstName + ' ' + Teachers[i].lastName;
        }
    }

    return teacherWithMostPupils;
}

string getTeacherWithTopPupils(teacher Teachers[], pupil Pupils[], int pupilCount)
{
    string teacherWithTopPupils = " ";
    int teacherId = 0;
    int bestPupil = Pupils[0].grade;
    for(int i = 1; i < pupilCount - 1; i++) {
        if (Pupils[i].grade > bestPupil) {
            bestPupil = Pupils[i].grade;
            teacherId = Pupils[i].teacherId;
        }
    }
    teacherWithTopPupils = Teachers[teacherId].firstName + ' ' + Teachers[teacherId].lastName;

    return teacherWithTopPupils;
}

int getAverageGrade(pupil Pupils[], int pupilCount)
{
    float averagePupilGrade = 0;
    for(int i = 0; i < pupilCount; i++) {
        averagePupilGrade += float(Pupils[i].grade);
    }
    averagePupilGrade = averagePupilGrade/float(pupilCount);

    return round(averagePupilGrade);
}

int getWorstTeacherCount(teacher Teachers[], int teacherCount, pupil Pupils[], int pupilCount, int averageGrade)
{
    int worstTeacherCount = 0;
    for(int i = 0; i < pupilCount; i++) {
        if (Pupils[i].grade < averageGrade) {
            worstTeacherCount++;
        }
    }

    return worstTeacherCount;
}

void getTeachersWithWorstPupils(teacher Teachers[], pupil Pupils[], int pupilCount, int averageGrade, string worstTeachers[])
{
    int temp = 0;
    for(int i = 0; i < pupilCount; i++) {
        if (Pupils[i].grade < averageGrade) {
          worstTeachers[temp] = Teachers[Pupils[i].teacherId].firstName + ' ' + Teachers[Pupils[i].teacherId].lastName;
          temp++;
        }
    }
}