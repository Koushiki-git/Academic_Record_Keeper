#include <iostream>    // Required for input/output operations (cin, cout)
#include <fstream>     // Required for file stream operations (ifstream, ofstream, fstream)
#include <iomanip>     // Required for output formatting (setw, setprecision)
#include <string>      // Required for string manipulation (std::string)
#include <limits>      // Required for numeric_limits to clear input buffer

// Define a class for Student
class Student
{
    int rollno;
    char name[50]; // Using char array for name as in original, though std::string is preferred in modern C++
    int p_marks, c_marks, m_marks, e_marks, cs_marks; // Marks for Physics, Chemistry, Maths, English, Computer Science
    float per;   // Percentage
    char grade;  // Grade based on percentage

    // Private helper function to calculate percentage and grade
    void calculate()
    {
        per = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0; // Calculate percentage
        if (per >= 60)
            grade = 'A';
        else if (per >= 50 && per < 60)
            grade = 'B';
        else if (per >= 33 && per < 50)
            grade = 'C';
        else
            grade = 'F'; // Fail if percentage is less than 33
    }

public:
    // Function to get student data from user
    void getdata()
    {
        std::cout << "\n\nEnter The roll number of student: ";
        std::cin >> rollno;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        std::cout << "\nEnter The Name of student: ";
        std::cin.getline(name, 50); // Use getline for names with spaces

        std::cout << "\nEnter The marks in Physics out of 100: ";
        std::cin >> p_marks;
        std::cout << "\nEnter The marks in Chemistry out of 100: ";
        std::cin >> c_marks;
        std::cout << "\nEnter The marks in Maths out of 100: ";
        std::cin >> m_marks;
        std::cout << "\nEnter The marks in English out of 100: ";
        std::cin >> e_marks;
        std::cout << "\nEnter The marks in Computer Science out of 100: ";
        std::cin >> cs_marks;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer after marks input

        calculate(); // Calculate percentage and grade after getting marks
    }

    // Function to display student data
    void showdata()
    {
        std::cout << "\nRoll number of student: " << rollno;
        std::cout << "\nName of student: " << name;
        std::cout << "\nMarks in Physics: " << p_marks;
        std::cout << "\nMarks in Chemistry: " << c_marks;
        std::cout << "\nMarks in Maths: " << m_marks;
        std::cout << "\nMarks in English: " << e_marks;
        std::cout << "\nMarks in Computer Science: " << cs_marks;
        std::cout << "\nPercentage of student is: " << std::setprecision(3) << per << "%"; // Set precision for percentage
        std::cout << "\nGrade of student is: " << grade;
    }

    // Function to display student data in tabular format
    void show_tabular()
    {
        std::cout << std::left << std::setw(10) << rollno
                  << std::setw(20) << name
                  << std::setw(5) << p_marks
                  << std::setw(5) << c_marks
                  << std::setw(5) << m_marks
                  << std::setw(5) << e_marks
                  << std::setw(5) << cs_marks
                  << std::setw(10) << std::fixed << std::setprecision(2) << per
                  << std::setw(5) << grade << std::endl;
    }

    // Function to return the roll number
    int retrollno() const // Marked const as it doesn't modify the object
    {
        return rollno;
    }
};

// Global declarations for file stream object and student object
std::fstream fp;
Student st;

// Function to write student record to file
void write_student()
{
    // Open file in output and append mode (ios::out | ios::app)
    fp.open("student.dat", std::ios::out | std::ios::app | std::ios::binary); // Use binary mode for objects
    st.getdata(); // Get data from user
    fp.write(reinterpret_cast<char*>(&st), sizeof(Student)); // Write object to file
    fp.close(); // Close the file
    std::cout << "\n\nStudent record has been created. Press Enter to continue...";
    std::cin.get(); // Wait for user to press Enter
}

// Function to read all records from file and display them
void display_all()
{
    // system("cls"); // For Windows, clear console screen. For cross-platform, handle differently.
    std::cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("student.dat", std::ios::in | std::ios::binary); // Open file in input mode
    if (!fp) // Check if file opening failed
    {
        std::cout << "ERROR!!! FILE COULD NOT BE OPENED\n\n Go To Entry Menu to create File";
        std::cout << "\n\n Program is closing ....";
        std::cin.get(); // Wait for user input
        return; // Exit function
    }

    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) // Read objects one by one
    {
        st.showdata(); // Display student data
        std::cout << "\n\n====================================\n";
        std::cout << "Press Enter to see next record...";
        std::cin.get(); // Wait for user to press Enter
    }
    fp.close(); // Close the file
    std::cout << "\nEnd of records. Press Enter to return to menu...";
    std::cin.get(); // Wait for user to press Enter
}

// Function to read a specific record from file and display it
void display_sp(int n)
{
    int flag = 0; // Flag to check if record is found
    fp.open("student.dat", std::ios::in | std::ios::binary); // Open file in input mode
    if (!fp) // Check if file opening failed
    {
        std::cout << "ERROR!!! FILE COULD NOT BE OPENED\n\n Go To Entry Menu to create File";
        std::cout << "\n\n Program is closing ....";
        std::cin.get(); // Wait for user input
        return; // Exit function
    }

    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) // Read objects one by one
    {
        if (st.retrollno() == n) // If roll number matches
        {
            // system("cls"); // Clear console screen
            st.showdata(); // Display specific student data
            flag = 1; // Set flag to indicate record found
            break; // Exit loop as record is found
        }
    }
    fp.close(); // Close the file
    if (flag == 0) // If record not found
        std::cout << "\n\nRecord not exist. Press Enter to continue...";
    std::cin.get(); // Wait for user to press Enter
}

// Function to modify record of file
void modify_student()
{
    int no, found = 0; // Variable for roll number, flag for found status
    // system("cls"); // Clear console screen
    std::cout << "\n\n\tTo Modify Record";
    std::cout << "\n\n\tPlease Enter The roll number of student: ";
    std::cin >> no;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    // Open file in input and output mode (ios::in | ios::out)
    fp.open("student.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!fp) // Check if file opening failed
    {
        std::cout << "ERROR!!! FILE COULD NOT BE OPENED\n\n Go To Entry Menu to create File";
        std::cout << "\n\n Program is closing ....";
        std::cin.get(); // Wait for user input
        return; // Exit function
    }

    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && found == 0) // Read and loop until found
    {
        if (st.retrollno() == no) // If roll number matches
        {
            st.showdata(); // Show current data
            std::cout << "\nPlease Enter The New Details of student" << std::endl;
            st.getdata(); // Get new data
            long int pos = -1 * static_cast<long int>(sizeof(st)); // Calculate position to move back
            fp.seekp(pos, std::ios::cur); // Move put pointer back to overwrite
            fp.write(reinterpret_cast<char*>(&st), sizeof(Student)); // Write updated object
            std::cout << "\n\n\tRecord Updated. Press Enter to continue...";
            found = 1; // Set found flag
        }
    }
    fp.close(); // Close the file
    if (found == 0) // If record not found
        std::cout << "\n\n Record Not Found. Press Enter to continue...";
    std::cin.get(); // Wait for user to press Enter
}

// Function to delete record of file
void delete_student()
{
    int no; // Variable for roll number to delete
    // system("cls"); // Clear console screen
    std::cout << "\n\n\n\tDelete Record";
    std::cout << "\n\nPlease Enter The roll number of student You Want To Delete: ";
    std::cin >> no;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    fp.open("student.dat", std::ios::in | std::ios::binary); // Open original file
    if (!fp) // Check if file opening failed
    {
        std::cout << "ERROR!!! FILE COULD NOT BE OPENED\n\n Go To Entry Menu to create File";
        std::cout << "\n\n Program is closing ....";
        std::cin.get(); // Wait for user input
        return; // Exit function
    }

    std::ofstream fp2; // Create a temporary file stream
    fp2.open("Temp.dat", std::ios::out | std::ios::binary); // Open temp file in output mode

    fp.seekg(0, std::ios::beg); // Go to beginning of original file

    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) // Read objects
    {
        if (st.retrollno() != no) // If roll number does not match, write to temp file
        {
            fp2.write(reinterpret_cast<char*>(&st), sizeof(Student));
        }
    }
    fp2.close(); // Close temp file
    fp.close(); // Close original file

    std::remove("student.dat"); // Delete original file
    std::rename("Temp.dat", "student.dat"); // Rename temp file to original file name

    std::cout << "\n\n\tRecord Deleted. Press Enter to continue...";
    std::cin.get(); // Wait for user to press Enter
}

// Function to display all students' grade report in tabular format
void class_result()
{
    // system("cls"); // Clear console screen
    fp.open("student.dat", std::ios::in | std::ios::binary); // Open file in input mode
    if (!fp) // Check if file opening failed
    {
        std::cout << "ERROR!!! FILE COULD NOT BE OPENED\n\n Go To Entry Menu to create File";
        std::cout << "\n\n Program is closing ....";
        std::cin.get(); // Wait for user input
        return; // Exit function
    }

    std::cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
    std::cout << "=================================================================\n";
    std::cout << std::left << std::setw(10) << "Roll No."
              << std::setw(20) << "Name"
              << std::setw(5) << "P"
              << std::setw(5) << "C"
              << std::setw(5) << "M"
              << std::setw(5) << "E"
              << std::setw(5) << "CS"
              << std::setw(10) << "%age"
              << std::setw(5) << "Grade" << std::endl;
    std::cout << "=================================================================\n";

    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) // Read and display all records
    {
        st.show_tabular();
    }
    fp.close(); // Close the file
    std::cout << "\nPress Enter to return to menu...";
    std::cin.get(); // Wait for user to press Enter
}

// Function to display result menu
void result_menu() // Renamed to avoid conflict with `result` keyword if used elsewhere
{
    int ans, rno;
    char ch;
    // system("cls"); // Clear console screen
    std::cout << "\n\n\nRESULT MENU";
    std::cout << "\n\n1. Class Result (All Students)\n\n2. Student Report Card\n\n3.Back to Main Menu";
    std::cout << "\n\n\nEnter Choice (1/2/3)? ";
    std::cin >> ans;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    switch (ans)
    {
    case 1:
        class_result();
        break;
    case 2:
    {
        char continue_display;
        do
        {
            // system("cls"); // Clear console screen
            std::cout << "\n\nEnter Roll Number Of Student: ";
            std::cin >> rno;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            display_sp(rno); // Display specific student report
            std::cout << "\n\nDo you want to See More Result (y/n)? ";
            std::cin >> continue_display;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        } while (continue_display == 'y' || continue_display == 'Y');
        break;
    }
    case 3:
        break; // Return to main menu
    default:
        std::cout << "\aInvalid choice! Press Enter to try again.";
        std::cin.get();
        result_menu(); // Call itself again for invalid input
    }
}

// Introduction Function
void intro()
{
    // system("cls"); // Clear console screen
    std::cout << "\n\n\n\n";
    std::cout << "\t\t\t\tSTUDENT\n";
    std::cout << "\t\t\t\tREPORT CARD\n";
    std::cout << "\t\t\t\tPROJECT\n";
    std::cout << "\n\nMADE BY : Your Name (e.g., SULABH AGRAWAL)"; // You can customize this
    std::cout << "\nSCHOOL : Your School (e.g., CAMBRIDGE SCHOOL)"; // You can customize this
    std::cout << "\n\n\nPress Enter to continue...";
    std::cin.get(); // Wait for user to press Enter
}

// Entry / Edit Menu Function
void entry_edit_menu() // Renamed for clarity and to avoid conflict
{
    // system("cls"); // Clear console screen
    char ch2;
    std::cout << "\n\n\n\tENTRY / EDIT MENU";
    std::cout << "\n\n\t1. CREATE STUDENT RECORD";
    std::cout << "\n\n\t2. DISPLAY ALL STUDENTS RECORDS";
    std::cout << "\n\n\t3. SEARCH STUDENT RECORD ";
    std::cout << "\n\n\t4. MODIFY STUDENT RECORD";
    std::cout << "\n\n\t5. DELETE STUDENT RECORD";
    std::cout << "\n\n\t6. BACK TO MAIN MENU";
    std::cout << "\n\n\tPlease Enter Your Choice (1-6): ";
    std::cin >> ch2;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    switch (ch2)
    {
    case '1':
        // system("cls");
        write_student();
        break;
    case '2':
        display_all();
        break;
    case '3':
        int num;
        // system("cls");
        std::cout << "\n\n\tPlease Enter The roll number: ";
        std::cin >> num;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        display_sp(num);
        break;
    case '4':
        modify_student();
        break;
    case '5':
        delete_student();
        break;
    case '6':
        break; // Return to main menu
    default:
        std::cout << "\aInvalid choice! Press Enter to try again.";
        std::cin.get();
        entry_edit_menu(); // Call itself again for invalid input
    }
}

// The main function of program
int main()
{
    char ch;
    intro(); // Display introduction

    do
    {
        // system("cls"); // Clear console screen
        std::cout << "\n\n\n\tMAIN MENU";
        std::cout << "\n\n\t01. RESULT MENU";
        std::cout << "\n\n\t02. ENTRY/EDIT MENU";
        std::cout << "\n\n\t03. EXIT";
        std::cout << "\n\n\tPlease Select Your Option (1-3): ";
        std::cin >> ch;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        switch (ch)
        {
        case '1':
            // system("cls");
            result_menu(); // Go to result menu
            break;
        case '2':
            entry_edit_menu(); // Go to entry/edit menu
            break;
        case '3':
            return 0; // Exit program
        default:
            std::cout << "\aInvalid choice! Press Enter to try again.";
            std::cin.get(); // Wait for user input
        }
    } while (ch != '3'); // Continue until user chooses to exit

    return 0;
}
