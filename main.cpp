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
int getWorstPupilCount(pupil Pupils[], int pupilCount, int averageGrade);
void getTeachersWithWorstPupils(teacher Teachers[], pupil Pupils[], int pupilCount, int averageGrade,
                                                    string WorstTeachers[], int & worstTeacherCount);
bool in_array(string Arr[], string searchString, int arrCount);
void writeResults(teacher Teachers[], int teacherCount, string teacherWithMostPupils, string teacherWithTopPupils,
                                     string teachersWithWorstPupils[], int worstTeacherCount, const char filename[]);
int findLineCount(const char filename[]);

int main() {
    // declare Vars
    const char teachers[] = "mokytojai.txt",
               pupils[] = "mokiniai.txt",
               results[] = "rezultatai.txt";

    int teacherCount = findLineCount(teachers),
        pupilCount = findLineCount(pupils),
        averagePupilGrade,
        worstTeacherCount = 0;

    string teacherWithMostPupils,
           teacherWithTopPupils;

    teacher Teachers[teacherCount];
    pupil Pupils[pupilCount];

    // read Files
    readTeachers(Teachers, teacherCount, teachers);
    readPupils(Pupils, pupilCount, pupils);

    // assign teacher Ids to Pupils
    assignTeacherId(Teachers, teacherCount, Pupils, pupilCount);

    // count how many pupils each teacher has
    countPupils(Teachers, teacherCount, Pupils, pupilCount);

    // find teacher with most Pupils
    teacherWithMostPupils = getTeacherWithMostPupils(Teachers, teacherCount);

    // find teacher with best Pupils
    teacherWithTopPupils = getTeacherWithTopPupils(Teachers, Pupils, pupilCount);

    // declare Vars
    averagePupilGrade = getAverageGrade(Pupils, pupilCount);
    worstTeacherCount = getWorstPupilCount(Pupils, pupilCount, averagePupilGrade);
    string teachersWithWorstPupils[worstTeacherCount];

    // find teacher with worst Pupils
    getTeachersWithWorstPupils(Teachers, Pupils, pupilCount, averagePupilGrade,
                                                 teachersWithWorstPupils, worstTeacherCount);

    // write Results
    writeResults(Teachers, teacherCount, teacherWithMostPupils, teacherWithTopPupils,
                                         teachersWithWorstPupils, worstTeacherCount, results);

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

int getWorstPupilCount(pupil Pupils[], int pupilCount, int averageGrade)
{
    int worstTeacherCount = 0;
    for(int i = 0; i < pupilCount; i++) {
        if (Pupils[i].grade < averageGrade) {
            worstTeacherCount++;
        }
    }

    return worstTeacherCount;
}

bool in_array(string Arr[], string searchString, int arrCount)
{
    bool found = false;
    for(int i = 0; i < arrCount; i++) {
        if (Arr[i] == searchString) {
            found = true;
        }
    }

    return found;
}

void getTeachersWithWorstPupils(teacher Teachers[], pupil Pupils[], int pupilCount, int averageGrade,
                                string WorstTeachers[], int & worstTeacherCount)
{
    worstTeacherCount = 0;
    string teacher = " ";
    for(int i = 0; i < pupilCount; i++) {
        if (Pupils[i].grade < averageGrade) {
            teacher = Teachers[Pupils[i].teacherId].firstName + ' ' + Teachers[Pupils[i].teacherId].lastName;
            if (!in_array(WorstTeachers, teacher, worstTeacherCount)) {
                WorstTeachers[worstTeacherCount] = teacher;
                worstTeacherCount++;
            }
        }
    }
}

void writeResults(teacher Teachers[], int teacherCount, string teacherWithMostPupils, string teacherWithTopPupils,
                  string teachersWithWorstPupils[], int worstTeacherCount, const char filename[])
{
    ofstream out(filename);

    out << "Kiekvienas mokytojas turi mokiniu:\n";
    for(int i = 0; i < teacherCount; i++) {
        out << Teachers[i].lastName << " " << Teachers[i].studentCount << '\n';
    }
    out << "--------------------------------------------------------------\n";
    out << "Daugiausia mokiniu turi: " << teacherWithMostPupils << '\n';
    out << "--------------------------------------------------------------\n";
    out << "Geriausiai mokiniai mokosi pas: " << teacherWithTopPupils << '\n';
    out << "--------------------------------------------------------------\n";
    out << "Mokiniu vidurkis nesiekia bendro mokiniu vidurkio pas: " << '\n';
    for(int i = 0; i < worstTeacherCount; i++) {
        if (teachersWithWorstPupils[i] != " ") {
        out << "# " << teachersWithWorstPupils[i] << '\n';
        }
    }
    out.close();
}