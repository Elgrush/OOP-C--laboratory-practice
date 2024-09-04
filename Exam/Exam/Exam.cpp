//3 вариант
//eklyshinsky@hse.ru

#include <iostream>
#include <vector>
#include <deque>

class LaboratoryPractice {
private:
    int number;
public:
    static const int NUMBER_OF_LABS = 10;

    int getNumber() const {
        return this->number;
    }
    void setNumber(int &number){
        this->number = number;
    }

    LaboratoryPractice(){}
    LaboratoryPractice(int number) {
        if(number > 0)
            this->number = number;
    }

    ~LaboratoryPractice(){}
};

class Student {
private:
    std::vector<LaboratoryPractice> labs;
    int additionalLabs = 0;
public:
    const std::vector<LaboratoryPractice> getLabs() const{
        return this->labs;
    }

    int getAdditionalLabs() const {
        return additionalLabs;
    }

    void addLabToDo(){
        ++additionalLabs;
    }

    void addLab() {
        for (int i = 1; i <= LaboratoryPractice::NUMBER_OF_LABS+additionalLabs; i++) {
            bool add = 1;
            for (int j = 0; j < labs.size(); j++) {
                if (labs[j].getNumber() == i) {
                    add = 0;
                    break;
                }
            }
            if (add) {
                labs.push_back(LaboratoryPractice(i));
                return;
            }
        }
    }

    void addLab(int n) {
        bool add = 1;
        for (int j = 0; j < labs.size(); j++) {
            if (labs[j].getNumber() == n) {
                return;
            }
        }
        labs.push_back(LaboratoryPractice(n));
    }

    Student() {};
    Student(int n) {
        addLab(n);
    }
    Student(std::vector<int> n) {
        for (int i = 0; i < n.size(); i++) {
            addLab(n[i]);
        }
    }
    Student(const Student& student) {
        this->labs = student.labs;
    }

    ~Student() {};
};

class StudentDeque {
private: 
    std::deque<Student*> students;
public:
    void pass() {
        delete students.front();
        students.pop_front();
    }

    void send_back() {
        students.push_back(students.front());
        students.pop_front();
    }

    int getLength()const {
        return students.size();
    }

    Student* getNext() {
        return students.front();
    }

    const Student* getNext() const {
        return students.front();
    }

    bool empty()const{
        return students.empty();
    }

    StudentDeque() {};

    StudentDeque(std::deque<Student> studentQueue) {
        for (int i = 0; i < studentQueue.size(); i++) {
            Student *student = new Student(studentQueue[i]);
            students.push_back(student);
        }
    }

    StudentDeque(StudentDeque &studentDeque) {
        for (int i = 0; i < studentDeque.students.size(); i++) {
            Student* student = new Student(*studentDeque.students[i]);
        }
    }

    ~StudentDeque() {
        while (!students.empty()) {
            delete students.front();
            students.pop_front();
        }
    };
};

class Teacher {
protected:
    double dushnilnostCoefficient = 0;
public:
    enum type{
        GoodTeacher, NotSoGoodTeacher
    };

    bool checkStudent(Student &student) {
        if (student.getLabs().size() < LaboratoryPractice::NUMBER_OF_LABS+student.getAdditionalLabs()) {
            student.addLab();
            return 0;
        }
        
        if ((abs((double)std::rand())) / RAND_MAX >= dushnilnostCoefficient) {
            return 1;
        }
        student.addLabToDo();
        return 0;
    }

    void checkNextStudent(StudentDeque& studentDeque) {
        Student* student = studentDeque.getNext();
        if (checkStudent(*student)) {
            studentDeque.pass();
        }
        else {
            studentDeque.send_back();
        }
    }

    Teacher() {
        srand(time(0));
    };

    ~Teacher() {};

    virtual Teacher::type id() const = 0;

    double getDushnilnostCoefitient()const {
        return dushnilnostCoefficient;
    };
};

class GoodTeacher : public Teacher {
public:
    GoodTeacher() {
        dushnilnostCoefficient = 0.25;
    }

    Teacher::type id() const override { return Teacher::type::GoodTeacher; };
};

class NotSoGoodTeacher : public Teacher {
public:
    NotSoGoodTeacher() {
        dushnilnostCoefficient = 0.5;
    }
    Teacher::type id() const override { return Teacher::type::NotSoGoodTeacher; };
};

int main()
{
    //В моей програме лабораторок 10, вписываете в количество что хотите, нумерация с единицы

    Student s1, s2, s3, s4, s5, s6;

    s1.addLab();

    StudentDeque students1(std::deque<Student> { s1, s2, s3, s4, s5, s6 } );

    StudentDeque students2(std::deque<Student> { s1, s2, s3, s4, s5, s6 });

    StudentDeque students3(std::deque<Student> { s1, s2, s3, s4, s5, s6 });

    int iteration_counter_for_a_test= 0;

    GoodTeacher teacher1;
    while (!students1.empty()) {
        teacher1.checkNextStudent(students1);
        ++iteration_counter_for_a_test;
    }

    std::cout << "Good: " << iteration_counter_for_a_test << std::endl;

    iteration_counter_for_a_test = 0;

    NotSoGoodTeacher teacher2;
    while (!students2.empty()) {
        teacher2.checkNextStudent(students2);
        ++iteration_counter_for_a_test;
    }

    std::cout << "Evil: " << iteration_counter_for_a_test << std::endl;

    Teacher *t1 = new GoodTeacher, *t2 = new GoodTeacher,
        *t3 = new NotSoGoodTeacher, *t4 = new NotSoGoodTeacher;

    std::vector<Teacher*> teachers = { t1, t2, t3, t4 };
    while (!students3.empty()) {
        for (int i = 0; i < teachers.size() && !students3.empty(); i++) {
            teachers[i]->checkNextStudent(students3);
            ++iteration_counter_for_a_test;
        }
    }

    std::cout << "Random prepod iteration:" << iteration_counter_for_a_test << std::endl;
}
