#include "Extractor.h"

/**
 * @brief Standard Constructor, sets all the attributes to their respective empty values
 * @details Time complexity: O(1)
 */
Extractor::Extractor() {
    this->students = set<Student>();
    this->schedules = vector<Schedule>();
    this->requests = queue<Request>();
}

/**
 * @brief Runs read methods and fills Extractor's attributes
 * @see readClassesPerUc()
 * @see readStudentsClasses()
 * @see readClasses()
 */
void Extractor::readFiles() {
    readClassesPerUc();
    readStudentsClasses();
    readClasses();
}

/**
 * @brief Read "classes_per_uc.csv" file and fills Extractor's vector of schedules with only classes: course units and classCode
 * @details Time complexity: O(n), where "n" is the number of files's lines
 */
void Extractor::readClassesPerUc() {
    fstream file("../data/classes_per_uc.csv");

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    string line;
    getline(file, line); // Ignorar o cabeçalho

    while (getline(file, line)) {
        // Extracting Info
        istringstream ss(line);
        string ucCode, classCode;
        getline(ss, ucCode, ',');
        getline(ss, classCode);

        // classes_per_uc is ordered therefore schedules will be ordered by Class
        schedules.emplace_back(Class(ucCode, classCode));
    }
}

/**
 * @brief Read "students_classes.csv" file and updates Extractor's vector of Schedules with Students and fills Extractor's set of Students
 * @details Time complexity: O(n * (log m + log k)) where "n" is the number of files's lines, "m" is the number os students and k is the number of schedules
 */
void Extractor::readStudentsClasses() {
    fstream file("../data/students_classes.csv");

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    string line;
    getline(file, line); // Ignorar o cabeçalho

    while (getline(file, line)) {
        // Extracting Info
        istringstream ss(line);
        string id, name, ucCode, classCode;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, ucCode, ',');
        getline(ss, classCode);
        Student student(id, name);
        Class classInfo(ucCode, classCode);
        student.addClass(classInfo);

        // Placing the info in the students structure
        auto it = students.find(student);
        if (it != students.end()){
            student = *it;
            students.erase(student);
            student.addClass(classInfo);
            students.insert(student);
        }else students.insert(student);

        //Placing the info in the schedules structure
        unsigned index = searchSchedules(classInfo);
        schedules[index].addStudent(student);
    }
}

/**
 * @brief Read "classes.csv" file and updates Extractor's vector of Schedules with Lessons
 * @details  Time complexity:
 */
void Extractor::readClasses() {
    fstream file("../data/classes.csv");

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    string line;
    getline(file, line); // Ignorar o cabeçalho

    while(getline(file, line)) {
        istringstream ss(line);
        string ucCode, classCode, weekDay, type;
        float startHour, duration;

        getline(ss, classCode, ',');
        getline(ss, ucCode, ',');
        getline(ss, weekDay, ',');
        ss >> startHour;
        ss.ignore(1); // Ignorar a vírgula
        ss >> duration;
        ss.ignore(1); // Ignorar a vírgula
        getline(ss, type);

        Class classInfo(ucCode, classCode);
        Lesson lesson(weekDay, startHour, duration, type);
        unsigned index;
        index = searchSchedules(classInfo);
        schedules[index].addLesson(lesson);
    }
}

/**
 * @brief Method that prints the Schedule of a given Class
 * @details  Time complexity: O(n + log k), where "n" is the number of files's lines and "k" is the number of schedules
 * @param classCode by reference
 */
void Extractor::getClassSchedule(const string& classCode) const {
    map<Lesson, vector<Class>> orderedSchedule;

    for (const Schedule& schedule: schedules) {
        if (schedule.getClassInfo().getClassCode() == classCode) {
            for (const Lesson& lesson: schedule.getLessons()) {
                orderedSchedule[lesson].push_back(schedule.getClassInfo());
            }
        }
    }

    if (orderedSchedule.empty()) {
        cout << "Invalid UcCode" << endl;
        return;
    }

    cout << "---SCHEDULE---" << endl;
    string currentDay;
    for (pair<Lesson, vector<Class>> lesson : orderedSchedule) {
        if (lesson.first.getWeekDay() != currentDay){
            cout << "-> " << lesson.first.getWeekDay() << ": " << endl;
            currentDay = lesson.first.getWeekDay();
        }
        for (const Class& classInfo: lesson.second) {
            cout << "START_TIME: " << setw(5) << formatedHours(lesson.first.getStart()) << " END_TIME: "
                 << setw(5) << formatedHours(lesson.first.getStart() + lesson.first.getDuration())
                 << " TYPE: " << setw(5) << lesson.first.getType() << " UC_CODE: "
                 << setw(5) << classInfo.getUcCode() << endl;
        }
    }
}

/**
 * @brief Method that prints the Schedule of a given Student
 * @details Time complexity: O(log m + k * (log p + f)), where "m" is the number os students, "k" is the number of student's classes, "p" is the number of maps's elements
 * and "f" is the number of lessons of a schedule
 * @param id by reference the student's id
 */
void Extractor::getStudentSchedule(const string& id) const {
    auto studentIt = students.find(Student(id, "PlaceHolder"));
    if (studentIt == students.end()) {
        cout << "Student not found!" << endl;
        return;
    }

    map<Lesson, vector<Class>> orderedSchedule;

    for (const Class& classInfo: studentIt->getClasses()) {
        Schedule schedule = schedules[searchSchedules(classInfo)];
        for (const Lesson& lesson: schedule.getLessons()) {
            orderedSchedule[lesson].push_back(classInfo);
        }
    }

    if (orderedSchedule.empty()) {
        cout << "Invalid UcCode" << endl;
        return;
    }

    cout << "STUDENT_NAME: " << studentIt->getName() << endl;
    cout << "---SCHEDULE---" << endl;
    string currentDay;
    for (pair<Lesson, vector<Class>> lesson : orderedSchedule) {
        if (lesson.first.getWeekDay() != currentDay){
            cout << "-> " << lesson.first.getWeekDay() << ": " << endl;
            currentDay = lesson.first.getWeekDay();
        }
        for (const Class& classInfo: lesson.second) {
            cout << "START_TIME: " << setw(5) << formatedHours(lesson.first.getStart()) << " END_TIME: "
            << setw(5) << formatedHours(lesson.first.getStart() + lesson.first.getDuration()) << " TYPE: "
            << setw(5) << lesson.first.getType() << " UC_CODE: " << setw(5) << classInfo.getUcCode()
            << " CLASS_CODE: " << setw(5) << classInfo.getClassCode() << endl;
        }
    }
}

/**
 * @brief Method that prints the Schedule of a given course unit
 * @details Time complexity: O(n * (log p * f)), where "n" is the number of schedules, "p" is the number of map's elements
 * and "f" is the number of lessons of a schedule
 * @param UcCode by reference
 */
void Extractor::getUcCodeSchedule(const string& UcCode) const {
    map<Lesson, vector<Class>> orderedSchedule;

    for (const Schedule& schedule : schedules) {
        if (schedule.getClassInfo().getUcCode() == UcCode) {
            for (const Lesson& lesson : schedule.getLessons()) {
                orderedSchedule[lesson].push_back(schedule.getClassInfo());
            }
        }
    }

    if (orderedSchedule.empty()) {
        cout << "Invalid UcCode" << endl;
        return;
    }

    cout << "---SCHEDULE---" << endl;
    string currentDay;
    for (pair<Lesson, vector<Class>> lesson : orderedSchedule) {
        if (lesson.first.getWeekDay() != currentDay){
            cout << "-> " << lesson.first.getWeekDay() << ": " << endl;
            currentDay = lesson.first.getWeekDay();
        }
        cout << "START_TIME: " << setw(5) << formatedHours(lesson.first.getStart()) << " END_TIME: "
             << setw(5) << formatedHours(lesson.first.getStart() + lesson.first.getDuration()) << " TYPE: "
             << setw(5) << lesson.first.getType() << " ClassCode: ";
        for (const Class& classInfo: lesson.second) {
            cout << classInfo.getClassCode() << " ";
        }
        cout << endl;
    }
}

/**
 * @brief Method that prints Students of a given Class
 * @details Time complexity: O(n * m + log n), where "n" is the number of students and "m" is the number of classes per student
 * @param classCode by reference the students's class
 * @param mode by reference the way the information will be sorted and then printed
 */
void Extractor::getClassStudents(const string& classCode, const int& mode) const {
    vector<Student> classStudents;
    for (const Student& student: students) {
        for (const Class& classInfo: student.getClasses()) {
            if (classInfo.getClassCode() == classCode) {
                classStudents.push_back(student);
                break;
            }
        }
    }
    cout << "CLASS_CODE: " << classCode << endl;
    sortAndPrintStudents(classStudents, mode);
}

/**
 * @brief Method that prints Students of a given course unit
 * @details Time complexity: O(n * m + log n), where "n" is the number of schedules and "m" is the number of students per schedule
 * @param ucCode by reference the students's ucCode
 * @param mode by reference the way the information will be sorted and then printed
 */
void Extractor::getUCStudents(const string& ucCode, const int& mode) const {
    vector<Student> ucStudents;

    for (const Schedule& schedule: schedules) {
        if (schedule.getClassInfo().getUcCode() == ucCode) {
            for (const Student& student: schedule.getStudents()) {
                ucStudents.push_back(student);
            }
        }
    }

    cout << "UC_CODE: " << ucCode << endl;
    sortAndPrintStudents(ucStudents, mode);
}

/**
 * @brief Method that prints Students of a given year
 * @details Time complexity: O(n * m + log n), where "n" is the number of students and "m" is the number of classes per student
 * @param year by reference the students's year
 * @param mode by reference the way the information will be sorted and then printed
 */
void Extractor::getYearStudents(const string& year, const int& mode) const {
    vector<Student> yearStudents;

    for (const Student& student: students) {
        for (const Class& classInfo: student.getClasses()) {
            if (classInfo.getClassCode()[0] == year[0]) {
                yearStudents.push_back(student);
                break;
            }
        }
    }
    cout << "YEAR: " << year << endl;
    sortAndPrintStudents(yearStudents, mode);
}

/**
 * @brief Method that prints the number of Students with a given value of course units
 * @details Time complexity: O(n), where "n" is the number of students
 * @param N by reference quantity of course units
 */
void Extractor::StudentsWithNUc(const int& N) const {
    int count = 0;
    for (const Student& student: students) {
        if (student.getClasses().size() >= N) count++;
    }
    cout << count << endl;
}

/**
 * @brief Method that prints the course units with the most Students
 * @details Time complexity: O(n * m + log m + m), where "n" is the number of students and "m" is the number of classes per student
 * @param N by reference quantity of course units with the most students
 */
void Extractor::TopNStudentsPerUC(const int& N) const {
    map<string, int> ucStudentCount;

    for (const Student& student : students) {
        for (const Class& classInfo : student.getClasses()) {
            string ucCode = classInfo.getUcCode();
            ucStudentCount[ucCode]++;
        }
    }

    vector<pair<string, int>> sortedUcs(ucStudentCount.begin(), ucStudentCount.end());

    auto compareUcs = [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    };

    sort(sortedUcs.begin(), sortedUcs.end(), compareUcs);

    cout << "A(s) " << N << " UC(s) com o maior numero de estudantes e(sao):" << endl;
    for (int i = 0; i < min(N, static_cast<int>(sortedUcs.size())); i++) {
        cout << i + 1 << ". " << sortedUcs[i].first << " (" << sortedUcs[i].second << " estudantes)" << endl;
    }
}

/**
 * @brief Function that emplaces new Requests in the queue
 * @details Time complexity: O(log n), where "n" is the number of students
 * @param studentId by reference
 * @param ucCode by reference
 * @param classCode by reference
 * @param type by reference
 */
void Extractor::newRequest(const string& studentId, const string& ucCode, const string& classCode, const string& type) {
    auto studentIt = students.find(Student(studentId, ""));

    if (studentIt == students.end()) {
        cout << "Student not Found!" << endl;
        return;
    }

    requests.emplace(*studentIt, Class(ucCode, classCode), type);
    cout << "Pedido Guardado" << endl;
}

/**
 * @brief Function that emplaces new Requests of type "S" in the queue
 * @details Time complexity: O(log m), where "m" is the number of students
 * @param studentId by reference
 * @param oldUcCode by reference
 * @param oldClassCode by reference
 * @param ucCode by reference
 * @param classCode by reference
 */
void Extractor::newRequest(const string& studentId, const string& oldUcCode, const string& oldClassCode, const string& ucCode, const string& classCode) {
    auto studentIt = students.find(Student(studentId, ""));

    if (studentIt == students.end()) {
        cout << "Student not Found!" << endl;
        return;
    }

    requests.emplace(*studentIt, Class(oldUcCode, oldClassCode), Class(ucCode, classCode));
    cout << "Pedido Guardado" << endl;
}

/**
 * @brief Function that processes first Request in the queue
 * @see processAdd(request)
 * @see processRemove(request)
 * @see processSwitch(request)
 */
void Extractor::processRequest() {
    if (requests.empty()) {
        cout << "No request to process" << endl;
        return;
    }

    Request request = requests.front();
    requests.pop();

    switch (request.getType()[0]) {
        case 'A':
            cout << "Processing Add Request from student " << request.getStudent().getName() << endl;
            processAdd(request);
            break;
        case 'R':
            cout << "Processing Remove Request from student " << request.getStudent().getName() << endl;
            processRemove(request);
            break;
        case 'S':
            cout << "Processing Switch Request from student " << request.getStudent().getName() << endl;
            processSwitch(request);
            break;
    }
}

/**
 * @brief Function that processes all Requests in the queue
 * @see processRequest()
 */
void Extractor::processAllRequests() {
    while (!requests.empty()) {
        processRequest();
    }
}

/**
 * @brief Function that processes the Request of type A in the queue
 * @details Time complexity: O(log n) + O(m) + O(s * log g * h + log j * k * w) + O(log q) + O(z + 2log z) + O(2log a + 2a) + O(2log u )
 * @see isSchedulePossible(const Student& student, const Class& newClass)
 * @see isBalanceMaintained(const Class& classInfo)
 * @param request by reference
 */
void Extractor::processAdd(const Request& request) {
    // Checking if Student is enrolled in 7 UC
    if (request.getStudent().getClasses().size() >= 7) {
        cout << "Request Denied" << endl;
        cout << "Reason: Student is already enrolled in 7 UC" << endl;
        return;
    }

    // Checking if class exists
    if (searchSchedules(request.getTargetClass()) == -1) { //O(log n)
        cout << "Request Denied" << endl;
        cout << "Reason: The following class does not exist" << endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
        return;
    }

    // Checking if Student is already enrolled in target UC
    for (const Class& classInfo: request.getStudent().getClasses()) { //O(m)
        if (classInfo.getUcCode() == request.getTargetClass().getUcCode()) {
            cout << "Request Denied" << endl;
            cout << "Reason: Student is already enrolled in target UC" << endl;
            return;
        }
    }

    // Checking if resulting schedule is possible
    if (!isSchedulePossible(request.getStudent(), request.getTargetClass())) { //O(s * log g * h + log j * k * w)
        cout << "Request Denied" << endl;
        cout << "Reason: Schedule is not compatible" << endl;
        return;
    }

    // Checking if target class has available space
    unsigned index = searchSchedules(request.getTargetClass()); //O(log q)
    if (schedules[index].getStudents().size() > 40) {
        cout << "Request Denied" << endl;
        cout << "Reason: Class is at capacity" << endl;
        return;
    }

    // Checking if class balance is maintained
    if (!isBalanceMaintained(request.getTargetClass())) { //O(z + 2log z)
        cout << "Request Denied" << endl;
        cout << "Reason: Class balance is not maintained" << endl;
        return;
    }

    // Adicionar a classe do aluno
    auto itr = students.find(request.getStudent()); //O(log a)
    Student student = *itr;
    students.erase(request.getStudent()); // O(a)
    student.addClass(request.getTargetClass()); // O(a)
    students.insert(student); // O(log a)

    // Adicionar o aluno ao horário
    index = searchSchedules(request.getTargetClass()); // O(log u)
    schedules[index].getStudents().insert(request.getStudent()); // O(log u)
    cout << "Request Approved" << endl;
    addRecord(request);
}

/**
 * @brief Function that processes the Request of type R in the queue
 * @details Time complexity: O(log n) + O(n) + O(l) + O(log n) + O(log l) + O(log n) + O(x),
 * where "n" is the number of students, "l" is the number of classes of a given student and "x" is the number of schedules of a created set
 * @param request by reference
 */
void Extractor::processRemove(const Request& request) {
    // Remover a classe do aluno
    auto itr = students.find(request.getStudent()); //O(log n)
    Student student = *itr;
    students.erase(request.getStudent()); // O(n)
    student.removeClass(request.getTargetClass()); // O(l)
    students.insert(student); // O(log n)

    // Remover o aluno do horário
    unsigned index = searchSchedules(request.getTargetClass()); // O(log l)

    if (index == -1) {
        cout << "Request Denied" << endl;
        cout << "Reason: The following class does not exist" <<  endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
    }

    set<Student>& scheduleStudents = schedules[index].getStudents();
    auto scheduleItr = scheduleStudents.find(request.getStudent()); //O(log n)
    if (scheduleItr != scheduleStudents.end()) {
        scheduleStudents.erase(scheduleItr); //O(x)
        cout << "Request Approved" << endl;
        addRecord(request);
    } else {
        cout << "Request Denied" << endl;
        cout << "Reason: Student is not enrolled in the following class" <<  endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
    }
}

/**
 * @brief Function that processes the Request of type R in the queue
 * @details Time complexity: O(log n * log m) + O(k) + O(n * log m * p + log m * l * a) + O(n + log n)
 * @see isSchedulePossible(const Student& student, const Class& newClass, const Class& auxClass)
 * @see isBalanceMaintained(const Class& classInfo, const Class& auxClass)
 * @param request by reference
 */
void Extractor::processSwitch(const Request& request) {
    // Checking if Student is enrolled in 7 UC
    if (request.getStudent().getClasses().size() > 7) {
        cout << "Request Denied" << endl;
        cout << "Reason: Student is already enrolled in 7 UC" << endl;
        return;
    }

    // Checking if classes exist
    if (searchSchedules(request.getTargetClass()) == -1 or //O(log n * log m)
        searchSchedules(request.getAuxClass()) == -1) {
        cout << "Request Denied" << endl;
        cout << "Reason: The following class does not exist" << endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
        return;
    }

    // Checking if Student is already enrolled in UC that is going to be added
    // And if Student is not enrolled in the UC to be removed
    bool found = false;
    for (const Class& classInfo: request.getStudent().getClasses()) { //O(k)
        if (classInfo.getUcCode() == request.getAuxClass().getUcCode()) {
            cout << "Request Denied" << endl;
            cout << "Reason: Student is already enrolled in target UC" << endl;
            return;
        } else if (classInfo.getUcCode() == request.getTargetClass().getUcCode()) {
            found = true;
        }
    }
    if (!found) {
        cout << "Request Denied" << endl;
        cout << "Reason: Student is not enrolled in the following class" << endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
        return;
    }

    // Checking if resulting schedule is possible //O(n * log m * p + log m * l * a)
    if (!isSchedulePossible(request.getStudent(), request.getTargetClass(), request.getAuxClass())) {
        cout << "Request Denied" << endl;
        cout << "Reason: Schedule is not compatible" << endl;
        return;
    }

    // Checking if target class has available space
    unsigned index = searchSchedules(request.getTargetClass());
    if (schedules[index].getStudents().size() > 40) {
        cout << "Request Denied" << endl;
        cout << "Reason: Class is at capacity" << endl;
        return;
    }

    // Checking if class balance is maintained //O(n + log n)
    if (!isBalanceMaintained(request.getTargetClass(), request.getAuxClass())) {
        cout << "Request Denied" << endl;
        cout << "Reason: Class balance is not maintained" << endl;
        return;
    }
}

/**
 * @brief A binary search for Schedules using their Class attribute
 * @details Time complexity: O(log n), where "n" is the number of schedules
 * @param classInfo by reference a Class to search in the vector
 * @return Int index of the class in the vector
 */
unsigned Extractor::searchSchedules(const Class& classInfo) const {
    unsigned low = 0, high = schedules.size()-1, middle = high/2;
    while (low <= high) {
        if (schedules[middle].getClassInfo() == classInfo) return middle;
        if (schedules[middle].getClassInfo() < classInfo) low = middle + 1;
        else high = middle - 1;
        middle = (low + high)/2;
    }
    return -1;
}

/**
 * @brief Check if a Student's name is lower that other
 * @details Time complexity: O(1)
 * @param a first Student to compare
 * @param b second Student to compare
 * @return True if first Student's name is lower than second, false otherwise
 */
bool Extractor::studentAlphabetical(const Student& a, const Student& b) {
    return a.getName() < b.getName();
}

/**
 * @brief Check if a Student's id is lower that other
 * @details Time complexity: O(1)
 * @param a first Student to compare
 * @param b second Student to compare
 * @return True if first Student's id is lower than second, false otherwise
 */
bool Extractor::studentNumerical(const Student& a, const Student& b) {
    return a.getId() < b.getId();
}

/**
 * @brief A function that prints the Students in a specific sorted manner
 * @details Time complexity: O(n + log n), where "n" is the number of students
 * @param students by reference
 * @param mode by reference
 */
void Extractor::sortAndPrintStudents(vector<Student>& students, const int& mode) {
    switch (mode) {
        case 1:
            sort(students.begin(), students.end(), studentAlphabetical);
            cout << "SORTED ALPHABETICALLY FROM FIRST TO LAST" << endl;
            break;
        case 2:
            sort(students.rbegin(), students.rend(), studentAlphabetical);
            cout << "SORTED ALPHABETICALLY FROM LAST TO FIRST" << endl;
            break;
        case 3:
            sort(students.begin(), students.end(), studentNumerical);
            cout << "SORTED NUMERICALLY FROM FIRST TO LAST" << endl;
            break;
        case 4:
            sort(students.rbegin(), students.rend(), studentNumerical);
            cout << "SORTED NUMERICALLY FROM LAST TO FIRST" << endl;
            break;
    }

    for (const Student& student: students) {
        cout << "ID: " << student.getId() << " NAME: " << student.getName() << endl;
    }
}

/**
 * @brief Receives a floating-point number and converts it to the American time format
 * @details Time complexity: O(1)
 * @param floathour by reference
 * @return String in the American time format
 */
string Extractor::formatedHours(const float& floathour) {
    int hour = floathour;
    int minutes = (floathour - hour) * 60;

    string Pm_Am = "AM";

    ostringstream oss;
    if (hour > 12) {
        hour = hour - 12;
        Pm_Am = "PM";
    }
    oss << setw(2) << setfill('0') << hour << ":" << setw(2)
    << setfill('0') << minutes << " " << Pm_Am;
    return oss.str();
}

/**
 * @brief A function that checks if a given Request conflicts with a student's schedule
 * @details Time complexity: O(n * log m * p + log m * l * a), where "n" is the number of student's classes, "m" is the number of shedules per class
 *"p" is the number of lessons per schedule, "l" is the number of lessons of the new schedule and "a" is the number of durations of each lesson
 * @param student by reference
 * @param newClass by reference
 * @return True if the Request doesn't conflicts with the Student's Schedule, false otherwise
 */
bool Extractor::isSchedulePossible(const Student& student, const Class& newClass) {
    map<Lesson, vector<Class>> orderedSchedule;

    for (const Class& classInfo: student.getClasses()) {
        Schedule schedule = schedules[searchSchedules(classInfo)];
        for (const Lesson& lesson: schedule.getLessons()) {
            orderedSchedule[lesson].push_back(classInfo);
        }
    }

    Schedule newSchedule = schedules[searchSchedules(newClass)];
    for (const Lesson& lesson: newSchedule.getLessons()) {
        if (lesson.getType() == "T") continue;
        for (int i = 0; i < lesson.getDuration()/0.5; i++) {
            if (orderedSchedule.find(Lesson(lesson, lesson.getStart()+(i*0.5), "PL")) != orderedSchedule.end()) return false;
            if (orderedSchedule.find(Lesson(lesson, lesson.getStart()+(i*0.5), "TP")) != orderedSchedule.end()) return false;
        }
    }

    return true;
}

/**
 * @brief A function that checks if a given Request of type "S" conflicts with a Student's schedule
 * @details Time complexity: O(n * log m * p + log m * l * a), where "n" is the number of student's classes, "m" is the number of shedules per class
 *"p" is the number of lessons per schedule, "l" is the number of lessons of the new schedule and "a" is the number of durations of each lesson
 * @param student by reference
 * @param newClass by reference
 * @param auxClass by reference
 * @return True if the Request doesn't conflicts with the Student's Schedule, false otherwise
 */
bool Extractor::isSchedulePossible(const Student& student, const Class& newClass, const Class& auxClass) {
    map<Lesson, vector<Class>> orderedSchedule;

    for (const Class& classInfo: student.getClasses()) {
        if (classInfo == auxClass) continue;
        Schedule schedule = schedules[searchSchedules(classInfo)];
        for (const Lesson& lesson: schedule.getLessons()) {
            orderedSchedule[lesson].push_back(classInfo);
        }
    }

    Schedule newSchedule = schedules[searchSchedules(newClass)];
    for (const Lesson& lesson: newSchedule.getLessons()) {
        if (lesson.getType() == "T") continue;
        for (int i = 0; i < lesson.getDuration()/0.5; i++) {
            if (orderedSchedule.find(Lesson(lesson, lesson.getStart()+(i*0.5), "PL")) != orderedSchedule.end()) return false;
            if (orderedSchedule.find(Lesson(lesson, lesson.getStart()+(i*0.5), "TP")) != orderedSchedule.end()) return false;
        }
    }

    return true;
}

/**
 * @brief A function that checks if a given Request conflicts with the Class's balance
 * @details Time complexity: O(n + log n), where "n" is the number of schedules
 * @param classInfo by reference
 * @return True if the Request doesn't conflicts with the Class's balance, false otherwise
 */
bool Extractor::isBalanceMaintained(const Class& classInfo) {
    int targetSize = schedules[searchSchedules(classInfo)].getStudents().size();
    int maximumSize = 0, minimumSize = 41;

    for (Schedule schedule: schedules) {
        int size = schedule.getStudents().size();
        if (size > maximumSize) maximumSize = size;
        if (size < minimumSize) minimumSize = size;
    }

    if (targetSize < maximumSize) return true;
    if (targetSize < minimumSize+4) return true;
    return false;
}

/**
 * @brief A function that checks if a given Request of type "S" conflicts with the Class's balance
 * @details Time complexity: O(n + 2log n), where "n" is the number of schedules
 * @param classInfo by reference
 * @param auxClass by reference
 * @return True if the Request doesn't conflicts with the Class's balance, false otherwise
 */
bool Extractor::isBalanceMaintained(const Class& classInfo, const Class& auxClass) {
    int targetSize = schedules[searchSchedules(classInfo)].getStudents().size();
    int auxSize = schedules[searchSchedules(auxClass)].getStudents().size();
    int maximumSize = 0, minimumSize = 41;

    for (Schedule schedule: schedules) {
        int size = schedule.getStudents().size();
        if (schedule.getClassInfo() == auxClass) size--;
        if (size > maximumSize) maximumSize = size;
        if (size < minimumSize) minimumSize = size;
    }

    if (auxSize-1 > targetSize) return true;
    if (targetSize < minimumSize+4) return true;
    return false;
}

/**
 * @brief Function to save information about processed requests
 * @details Time complexity: O(1)
 * @param request by reference
 */
void Extractor::addRecord(const Request& request) {
    ifstream infile("../data/records.csv");
    // Create and open Records file
    ofstream record("../data/records.csv");
    if (!infile.good()) { record << "StudentCode,StudentName,Type,TargetUcCode,TargetClassCode" << endl; }
    infile.close();

    record << request.getStudent().getId() << ',' << request.getStudent().getName() << ',';
    if (request.getType() == "A") record << "ADD";
    if (request.getType() == "R") record << "REMOVE";
    if (request.getType() == "S") record << "SWITCH";
    record << ',' << request.getTargetClass().getUcCode() << ',' << request.getTargetClass().getClassCode() << endl;
}