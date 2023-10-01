#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

// Define structure to store student information
struct Student {
    string name;
    int student_id;
    double assignment_score;
    double quiz_score;
    double exam_score;
    double overall_grade;
    string letter_grade;
    string feedbacks;
};

// Function to calculate overall grade based on user-defined weightage
double CalculateOverallGrade(double assignment_weight, double quiz_weight, double exam_weight, double assignment_score, double quiz_score, double exam_score) {
    const double total_assignment_marks = 15.0;
    const double total_quiz_marks = 25.0;
    const double total_exam_marks = 100.0;

    assignment_score = min(assignment_score, total_assignment_marks); // Limit assignment score to 15
    quiz_score = min(quiz_score, total_quiz_marks); // Limit quiz score to 25
    exam_score = min(exam_score, total_exam_marks); // Limit exam score to 100

    double normalized_assignment = (assignment_score / total_assignment_marks) * 100.0;
    double normalized_quiz = (quiz_score / total_quiz_marks) * 100.0;
    double normalized_exam = (exam_score / total_exam_marks) * 100.0;

    return (assignment_weight * normalized_assignment + quiz_weight * normalized_quiz + exam_weight * normalized_exam) / (assignment_weight + quiz_weight + exam_weight);
}

// Function to map numerical grade to letter grade
string MapToLetterGrade(double overall_grade) {
    if (overall_grade >= 80) {
        return "A";
    } else if (overall_grade >= 70) {
        return "B";
    } else if (overall_grade >= 60) {
        return "C";
    } else if (overall_grade >= 50) {
        return "D";
    } else {
        return "F";
    }
}

// Function to provide feedback based on the final grade
string GetFeedback(double overall_grade) {
    if (overall_grade >= 80) {
        return "Excellent!";
    } else if (overall_grade >= 70) {
        return "Good job!";
    } else if (overall_grade >= 60) {
        return "Satisfactory.";
    } else if (overall_grade >= 50) {
        return "Needs improvement.";
    } else {
        return "Failing grade. Student needs to work hard and improve various sides.";
    }
}

// Function to save student data to a file
void SaveStudentData(const vector<Student>& students) {
    ofstream outFile("student_data.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < students.size(); i++) {
            outFile << "Student Name: " << students[i].name << endl;
            outFile << "Student ID: " << students[i].student_id << endl;
            outFile << "Assignment Score: " << students[i].assignment_score << endl;
            outFile << "Quiz Score: " << students[i].quiz_score << endl;
            outFile << "Exam Score: " << students[i].exam_score << endl;
            outFile << "Overall Grade: " << students[i].overall_grade << endl;
            outFile << "Letter Grade: " << students[i].letter_grade << endl;
            outFile << "Feedback: " << students[i].feedbacks << endl;
            outFile << endl;
        }

        cout << "Student data saved to 'student_data.txt'." << endl;
    } else {
        cerr << "Error: Unable to open the file for writing." << endl;
    }
}

// Function to load student data from a file
vector<Student> LoadStudentData() {
    vector<Student> students;
    ifstream inFile("student_data.txt");
    if (inFile.is_open()) {
        Student student;
        while (inFile >> student.name >> student.student_id >> student.assignment_score >> student.quiz_score >> student.exam_score >> student.overall_grade >> student.letter_grade) {
            getline(inFile, student.feedbacks);
            students.push_back(student);
        }
        inFile.close();
        cout << "Student data loaded from 'student_data.txt'." << endl;
    } else {
        cerr << "Error: Unable to open the file for reading." << endl;
    }
    return students;
}

int main() {
    vector<Student> students;
    int numStudents;
    double assignment_weight = 0.15, quiz_weight = 0.25, exam_weight = 0.60;

    cout << "Please enter the number of students: ";
    cin >> numStudents;

    // Clear the newline character from the buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cin.fail() || numStudents <= 0) {
        cerr << "Error: Invalid number of students. Please enter a positive integer." << endl;
        return 1;
    }

    for (int i = 0; i < numStudents; i++) {
        Student student;

        cout << "Enter the name of the student: ";
        getline(cin, student.name);

        if (student.name.empty()) {
            cerr << "Error: Student name cannot be empty." << endl;
            return 1;
        }

        cout << "Enter student ID: ";
        cin >> student.student_id;

        if (cin.fail() || student.student_id <= 0) {
            cerr << "Error: Invalid student ID. Please enter a positive integer." << endl;
            return 1;
        }

        cout << "Assignment score (0-15): ";
        cin >> student.assignment_score;

        if (cin.fail() || student.assignment_score < 0 || student.assignment_score > 15) {
            cerr << "Error: Invalid assignment score. Please enter a value between 0 and 15." << endl;
            return 1;
        }

        cout << "Quiz score (0-25): ";
        cin >> student.quiz_score;

        if (cin.fail() || student.quiz_score < 0 || student.quiz_score > 25) {
            cerr << "Error: Invalid quiz score. Please enter a value between 0 and 25." << endl;
            return 1;
        }

        cout << "Exam score (0-100): ";
        cin >> student.exam_score;

        if (cin.fail() || student.exam_score < 0 || student.exam_score > 100) {
            cerr << "Error: Invalid exam score. Please enter a value between 0 and 100." << endl;
            return 1;
        }

        student.overall_grade = CalculateOverallGrade(assignment_weight, quiz_weight, exam_weight, student.assignment_score, student.quiz_score, student.exam_score);
        student.letter_grade = MapToLetterGrade(student.overall_grade);
        student.feedbacks = GetFeedback(student.overall_grade);

        students.push_back(student);
    }

    // Ask the user if they want to save or load student data
    char choice;
    cout << "Do you want to save (S) or load (L) student data? (S/L): ";
    cin >> choice;

    if (cin.fail() || (choice != 'S' && choice != 's' && choice != 'L' && choice != 'l')) {
        cerr << "Error: Invalid choice. Please enter 'S' or 'L' to save or load student data." << endl;
        return 1;
    }

    if (choice == 'S' || choice == 's') {
        // Save student data
        SaveStudentData(students);
    } else {
        // Load student data
        students = LoadStudentData();
    }

    // Display the results of all students
    for (int i = 0; i < students.size(); i++) {
        cout << "Student Name: " << students[i].name << endl;
        cout << "Student ID: " << students[i].student_id << endl;
        cout << "Overall Grade: " << students[i].overall_grade << endl;
        cout << "Letter Grade: " << students[i].letter_grade << endl;
        cout << "Feedback: " << students[i].feedbacks << endl;
        cout << endl;
    }

    return 0;
}
