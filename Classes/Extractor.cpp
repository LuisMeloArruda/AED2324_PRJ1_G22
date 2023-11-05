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
    readClassesPerUc(); //O(n)
    readStudentsClasses(); //O(n * (log m + log k))
    readClasses(); //O(n * log m)
    readModifications(); //O(u * (log p + 2 * log s + c + (c - 1) * log s + l * log m + k * d * 2 * log m + s + log f + log p + n + log x))
}

/**
 * @brief Read "classes_per_uc.csv" file and fills Extractor's vector of schedules with only classes: course units and classCode
 * @details Time complexity: O(n), where "n" is the number of file's lines
 */
void Extractor::readClassesPerUc() {
    fstream file("../data/classes_per_uc.csv");

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
    }

    string line;
    getline(file, line); // Ignore header

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
 * @details Time complexity: O(n * (log m + log k)) where "n" is the number of file's lines, "m" is the number os students and k is the number of schedules
 */
void Extractor::readStudentsClasses() {
    fstream file("../data/students_classes.csv");

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
    }

    string line;
    getline(file, line); // Ignore Header

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

        //Placing the info in the schedules structure
        unsigned index = searchSchedules(classInfo);
        schedules[index].addStudent(student);

        student.addClass(classInfo);
        // Placing the info in the students structure
        auto placingInfo = students.insert(student);
        auto it = placingInfo.first;
        if (!placingInfo.second) {
            student = *it;
            it = students.erase(it);
            student.addClass(classInfo);
            students.insert(it, student);
        }
    }
}

/**
 * @brief Read "classes.csv" file and updates Extractor's vector of Schedules with Lessons
 * @details  Time complexity: O(n * log m), where "n" is the number of file's lines and m is the number of schedules
 */
void Extractor::readClasses() {
    fstream file("../data/classes.csv");

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
    }

    string line;
    getline(file, line); // Ignore Header

    while(getline(file, line)) {
        istringstream ss(line);
        string ucCode, classCode, weekDay, type;
        float startHour, duration;

        getline(ss, classCode, ',');
        getline(ss, ucCode, ',');
        getline(ss, weekDay, ',');
        ss >> startHour;
        ss.ignore(1); // Ignore comma
        ss >> duration;
        ss.ignore(1); // Ignore comma
        getline(ss, type);

        Class classInfo(ucCode, classCode);
        Lesson lesson(weekDay, startHour, duration, type);
        unsigned index;
        index = searchSchedules(classInfo);
        schedules[index].addLesson(lesson);
    }
}

/**
 * @brief Read "records.csv" file and create and process requests to update the current data
 * @details Time complexity: O(u * (log p + 2 * log s + c + (c - 1) * log s + l * log m + k * d * 2 * log m + s + log f + log p + n + log x))
 * where "u" is the number of modifications stored in the records file, "p" is the number of students, "s" is the number of schedules,
 * "c" is the number of classes, "l" is the number of lessons of the student, "m" is the number of lessons in the student's schedule,
 * "k" is the number of lessons in the new class, "d" is the number of slots the new lesson fills,
 * "f" is the number of students in the target class, "n" is the number of the given student's classes, "x" is the target schedule's number of students
 */
void Extractor::readModifications() {
    fstream file("../data/records.csv");
    if (!file.is_open()) return;

    string line;
    getline(file, line); // Ignore Header

    while(getline(file, line)) {
        istringstream ss(line);
        string studentCode, type, targetUcCode, targetClassCode, oldUcCode, oldClassCode;

        getline(ss, studentCode, ',');
        getline(ss, type, ',');
        getline(ss, targetUcCode, ',');
        getline(ss, targetClassCode, ',');
        getline(ss, oldUcCode, ',');
        getline(ss, oldClassCode);

        Request request = Request(Student(studentCode, ""), Class(targetUcCode, targetClassCode), type);
        if (type == "Add") {
            type = "A";
        }
        if (type == "Remove") {
            type = "R";
        }
        if (type == "Switch") {
            type = "S";
            request = Request(Student(studentCode, ""), Class(oldUcCode, oldClassCode), Class(targetUcCode, targetClassCode));
        }

        auto studentIt = students.find(Student(request.getStudent().getId(), "")); //O(log n)

        if (studentIt == students.end()) {
            cout << "Request Denied" << endl;
            cout << "Student not Found!" << endl;
            return;
        }else request.setStudent(*studentIt);

        switch (type[0]) {
            case 'A':
                processAdd(request, 0); //O(log s + c + c * log s + l * log m + k * d * 2 * log m + s + log p + log x)
                break;
            case 'R':
                processRemove(request, 0); //O(log s + log k + log p + n)
                break;
            case 'S':
                processSwitch(request, 0); //O(2 * log s + c + (c - 1) * log s + l * log m + k * d * 2 * log m + s + log f + log p + n + log x)
                break;
        }
    }

}

/**
 * @brief Method that prints the Schedule of a given Class
 * @details  Time complexity: O(n * log m + k), where "n" is the number of lessons of given class,
 * "m" is the number of keys in the map and "k" is the number of values in said map
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
 * @details Time complexity: O(log m + k * log s + l * log p + f), where "m" is the number of students, "k" is the number of the student's classes,
 * "s" is the number of schedules, "l" is the number of the student's lessons, "p" is the number of map's keys and "f" is the number of values in said map
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
        const Schedule& schedule = schedules[searchSchedules(classInfo)];
        for (const Lesson& lesson: schedule.getLessons()) {
            orderedSchedule[lesson].push_back(classInfo);
        }
    }

    if (orderedSchedule.empty()) {
        cout << "Student is not enrolled in any class" << endl;
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
 * @details TIme complexity: O(n * log m + f), where "n" is the number of lessons of given UC, "m" is the number of keys of map
 * and "f" is the number of values of said map
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
 * @details Time complexity: O(n + (s * log s + s)), where "n" is the sum of the classes of every student
 * and "s" is the number of students that belong to the given class
 * @param classCode by reference the students' class
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
    sortAndPrintStudents(classStudents, mode); // O(n * log n + n)
}

/**
 * @brief Method that prints Students of a given course unit
 * @details Time complexity: O(k + k * log k + k), where "k" is the number of students enrolled in the Uc
 * @param ucCode by reference the student's ucCode
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
    sortAndPrintStudents(ucStudents, mode); // O(n * log n + n)
}

/**
 * @brief Method that prints Students of a given year
 * @details Time complexity: O(n * m + k * log k + k) where "n" is the number of students, "m" is the number of classes per student
 * and "k" is the number of students that are enrolled in classes of the given year
 * @param year by reference the student's year
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
    sortAndPrintStudents(yearStudents, mode); // O(n * log n + n)
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
 * @details Time complexity: O(n * c * log m + m * log m + N), where "n" is the number of students and "c" is the number of classes per student,
 * "m" is the number of keys in the map and "N" is the number of top UCs to be displayed
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

    sort(sortedUcs.begin(), sortedUcs.end(), compareUcs); // O(n * log n)

    cout << "The " << N << " UC/s with the larger number of students is/are:" << endl;
    for (int i = 0; i < min(N, static_cast<int>(sortedUcs.size())); i++) {
        cout << i + 1 << ". " << sortedUcs[i].first << " (" << sortedUcs[i].second << " students)" << endl;
    }
}

/**
 * @brief Function that places new Requests in the queue
 * @details Time complexity: O(1)
 * @param studentId by reference
 * @param ucCode by reference
 * @param classCode by reference
 * @param type by reference
 */
void Extractor::newRequest(const string& studentId, const string& ucCode, const string& classCode, const string& type) {
    requests.emplace(Student(studentId, ""), Class(ucCode, classCode), type);
    cout << "Request Logged" << endl;
}

/**
 * @brief Function that places new Requests of type "S" in the queue
 * @details Time complexity: O(1)
 * @param studentId by reference
 * @param oldUcCode by reference
 * @param oldClassCode by reference
 * @param ucCode by reference
 * @param classCode by reference
 */
void Extractor::newRequest(const string& studentId, const string& oldUcCode, const string& oldClassCode, const string& ucCode, const string& classCode) {
    requests.emplace(Student(studentId, ""), Class(oldUcCode, oldClassCode), Class(ucCode, classCode));
    cout << "Request Logged" << endl;
}

/**
 * @brief Function that processes first Request in the queue
 * @details Time complexity: O(log p + 2 * log s + c + (c - 1) * log s + l * log m + k * d * 2 * log m + s + log f + log p + n + log x),
 * where "p" is the number of students, "s" is the number of schedules, "c" is the number of classes, "l" is the number of lessons of the student,
 * "m" is the number of lessons in the student's schedule, "k" is the number of lessons in the new class, "d" is the number of slots
 * the new lesson fills, "f" is the number of students in the target class, "n" is the number of the
 * given student's classes, "x" is the target schedule's number of students
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

    auto studentIt = students.find(Student(request.getStudent().getId(), ""));

    if (studentIt == students.end()) {
        cout << "Request Denied" << endl;
        cout << "Student not Found!" << endl;
        return;
    }else request.setStudent(*studentIt);

    switch (request.getType()[0]) {
        case 'A':
            cout << "Processing Add Request from student " << request.getStudent().getName() << endl;
            processAdd(request); //O(log s + c + c * log s + l * log m + k * d * 2 * log m + s + log p + log x)
            break;
        case 'R':
            cout << "Processing Remove Request from student " << request.getStudent().getName() << endl;
            processRemove(request); //O(log s + log k + log p + n)
            break;
        case 'S':
            cout << "Processing Switch Request from student " << request.getStudent().getName() << endl;
            processSwitch(request); //O(2 * log s + c + (c - 1) * log s + l * log m + k * d * 2 * log m + s + log f + log p + n + log x)
            break;
        default:
            cout << "Request Denied" << endl;
            cout << "Invalid Type" << endl;
            break;
    }
}

/**
 * @brief Function that processes all Requests in the queue
 * @details Time complexity: O(u * (log p + 2 * log s + c + (c - 1) * log s + l * log m + k * d * 2 * log m + s + log f + log p + n + log x)),
 * where "u" is the number of request in the queue to process, "p" is the number of students, "s" is the number of schedules,
 * "c" is the number of classes, "l" is the number of lessons of the student, "m" is the number of lessons in the student's schedule,
 * "k" is the number of lessons in the new class, "d" is the number of slots the new lesson fills, "f" is the number of students in the target class,
 * "n" is the number of the given student's classes, "x" is the target schedule's number of students
 * @see processRequest()
 */
void Extractor::processAllRequests() {
    while (!requests.empty()) {
        processRequest(); //O(log p + 2 * log s + c + (c - 1) * log s + l * log m + k * d * 2 * log m + s + log f + log p + n + log x)
    }
}

/**
 * @brief Function that processes the Request of type A in the queue
 * @details Time complexity: O(log s + c + c * log s + l * log m + k * d * 2 * log m + s + log p + log x), where "s" is the number of schedules,
 * "c" is the number of student's classes, "l" is the number of lessons of the student, "m" is the number of lessons in the student's schedule,
 * "k" is the number of lessons in the new class, "d" is the number of slots the new class fills, "p" is the number students
 * and "x" is the target schedule's number of students
 * @see isSchedulePossible(const Student& student, const Class& newClass)
 * @see isBalanceMaintained(const Class& classInfo)
 * @param request by reference
 */
void Extractor::processAdd(const Request& request, int print) {
    // Checking if Student is enrolled in 7 UC
    if (request.getStudent().getClasses().size() >= 7) {
        cout << "Request Denied" << endl;
        cout << "Reason: Student is already enrolled in 7 UC" << endl;
        return;
    }

    // Checking if class exists
    unsigned targetScheduleIndex = searchSchedules(request.getTargetClass()); //O(log n)
    if (targetScheduleIndex == -1) {
        cout << "Request Denied" << endl;
        cout << "Reason: The following class does not exist" << endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
        return;
    }

    // Checking if Student is already enrolled in target UC
    for (const Class& classInfo: request.getStudent().getClasses()) { //O(n)
        if (classInfo.getUcCode() == request.getTargetClass().getUcCode()) {
            cout << "Request Denied" << endl;
            cout << "Reason: Student is already enrolled in target UC" << endl;
            return;
        }
    }

    // Checking if resulting schedule is possible
    if (!isSchedulePossible(request.getStudent(), targetScheduleIndex)) { //O(c * log s + l * log m + k * d * 2 * log m)
        cout << "Request Denied" << endl;
        cout << "Reason: Schedule is not compatible" << endl;
        return;
    }

    // Checking if target class has available space
    if (schedules[targetScheduleIndex].getStudents().size() > 40) {
        cout << "Request Denied" << endl;
        cout << "Reason: Class is at capacity" << endl;
        return;
    }

    // Checking if class balance is maintained
    if (!isBalanceMaintained(targetScheduleIndex)) { //O(n)
        cout << "Request Denied" << endl;
        cout << "Reason: Class balance is not maintained" << endl;
        return;
    }

    // Finding student
    auto itr = students.find(request.getStudent()); //O(log n)

    // Adding student to schedule
    schedules[targetScheduleIndex].getStudents().insert(Student(itr->getId(), itr->getName()));// O(log n)

    // Adding class to student
    Student student = *itr;
    itr = students.erase(itr);
    student.addClass(request.getTargetClass());
    students.insert(itr, student);

    if (print) {
        cout << "Request Approved" << endl;
        addRecord(request);
    }
}

/**
 * @brief Function that processes the Request of type R in the queue
 * @details Time complexity: O(log s + log k + log p + n), where "s" is the number of schedules, "k" is the number of students in the target schedule,
 * "p" is the number of students and "n" is the number of the student's classes
 * @param request by reference
 */
void Extractor::processRemove(const Request& request, int print) {
    // Removing student from schedule
    unsigned targetScheduleIndex = searchSchedules(request.getTargetClass());// O(log n)

    if (targetScheduleIndex == -1) {
        cout << "Request Denied" << endl;
        cout << "Reason: The following class does not exist" <<  endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
        return;
    }

    set<Student>& scheduleStudents = schedules[targetScheduleIndex].getStudents();
    auto scheduleItr = scheduleStudents.find(request.getStudent()); //O(log n)
    if (scheduleItr != scheduleStudents.end()) {
        scheduleStudents.erase(scheduleItr);
        if (print) {
            cout << "Request Approved" << endl;
            addRecord(request);
        }
    } else {
        cout << "Request Denied" << endl;
        cout << "Reason: Student is not enrolled in the following class" <<  endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
        return;
    }

    // Removing class from student
    auto itr = students.find(request.getStudent());//O(log n)
    Student student = *itr;
    itr = students.erase(itr);
    student.removeClass(request.getTargetClass()); //O(n)
    students.insert(itr, student);
}

/**
 * @brief Function that processes the Request of type S in the queue
 * @details Time complexity: O(2 * log s + c + (c - 1) * log s + l * log m + k * d * 2 * log m + s + log f + log p + n + log x),
 * where "s" is the number of schedules, "c" is the number of classes, "l" is the number of lessons of the student,
 * "m" is the number of lessons in the student's schedule, "k" is the number of lessons in the new class, "d" is the number of slots
 * the new lesson fills, "f" is the number of students in the target class, "p" is the number of students, "n" is the number of the
 * given student's classes, "x" is the target schedule's number of students
 * @see isSchedulePossible(const Student& student, const Class& newClass, const Class& auxClass)
 * @see isBalanceMaintained(const Class& classInfo, const Class& auxClass)
 * @param request by reference
 */
void Extractor::processSwitch(const Request& request, int print) {
    // Checking if Student is enrolled in 7 UC
    if (request.getStudent().getClasses().size() > 7) {
        cout << "Request Denied" << endl;
        cout << "Reason: Student is already enrolled in 7 UC" << endl;
        return;
    }

    // Checking if classes exist
    unsigned indexTargetClass = searchSchedules(request.getTargetClass()); //O(log n)
    unsigned indexAuxClass = searchSchedules(request.getAuxClass()); //O(log n)
    if ( indexTargetClass == -1 or
         indexAuxClass == -1) {
        cout << "Request Denied" << endl;
        cout << "Reason: The following class does not exist" << endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
        return;
    }

    // Checking if Student is already enrolled in UC that is going to be added
    // And if Student is not enrolled in the UC to be removed
    bool found = false;
    for (const Class& classInfo: request.getStudent().getClasses()) { //O(n)
        if (classInfo.getUcCode() == request.getAuxClass().getUcCode()) {
            found = true;
        } else if (classInfo.getUcCode() == request.getTargetClass().getUcCode()) {
            cout << "Request Denied" << endl;
            cout << "Reason: Student is already enrolled in target UC" << endl;
            return;
        }
    }
    if (!found) {
        cout << "Request Denied" << endl;
        cout << "Reason: Student is not enrolled in the following class" << endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
        return;
    }

    // Checking if resulting schedule is possible //O(c * log s + l * log m + k * d * 2 * log m)
    if (!isSchedulePossible(request.getStudent(), indexTargetClass, request.getAuxClass())) {
        cout << "Request Denied" << endl;
        cout << "Reason: Schedule is not compatible" << endl;
        return;
    }

    // Checking if target class has available space
    if (schedules[indexTargetClass].getStudents().size() > 40) {
        cout << "Request Denied" << endl;
        cout << "Reason: Class is at capacity" << endl;
        return;
    }

    // Checking if class balance is maintained //O(n)
    if (!isBalanceMaintained(indexTargetClass, indexAuxClass, request.getAuxClass())) {
        cout << "Request Denied" << endl;
        cout << "Reason: Class balance is not maintained" << endl;
        return;
    }

    // Removing student from schedule
    set<Student>& scheduleStudents = schedules[indexAuxClass].getStudents();
    auto scheduleItr = scheduleStudents.find(request.getStudent()); // O(log n)
    if (scheduleItr != scheduleStudents.end()) {
        scheduleStudents.erase(scheduleItr);
    } else {
        cout << "Request Denied" << endl;
        cout << "Reason: Student is not enrolled in the following class" <<  endl;
        cout << "UC: " << request.getTargetClass().getUcCode() << " CLASS_CODE: " << request.getTargetClass().getClassCode() << endl;
        return;
    }

    // Removing and Adding respective classes to Student
    auto itr = students.find(request.getStudent()); // O(log n)
    Student student = *itr;
    itr = students.erase(itr);
    student.removeClass(request.getAuxClass()); // O(n)
    student.addClass(request.getTargetClass());
    students.insert(itr, student);

    // Adding student to schedule
    schedules[indexTargetClass].getStudents().insert(Student(request.getStudent().getId(), request.getStudent().getName())); // O(log n)

    if (print) {
        cout << "Request Approved" << endl;
        addRecord(request);
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
 * @details Time complexity: O(n * log n + n), where "n" is the number of students
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
string Extractor::formatedHours(const float& floatHour) {
    int hour = floatHour;
    int minutes = (floatHour - hour) * 60;

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
 * @details Time complexity: O(c * log s + l * log m + k * d * 2 * log m), where "c" is the number of student's classes,
 * "s" is the number of schedules, "l" is the number of lessons of the student, "m" is the number of keys of the map,
 * "k" is the number of lessons in the new class, "d" is the number of slots the new lesson fills
 * @param student by reference
 * @param newClass by reference
 * @return True if the Request doesn't conflicts with the Student's Schedule, false otherwise
 */
bool Extractor::isSchedulePossible(const Student& student, const unsigned& newClassScheduleIndex) const {
    map<Lesson, vector<Class>> orderedSchedule;

    for (const Class& classInfo: student.getClasses()) {
        const Schedule& schedule = schedules[searchSchedules(classInfo)];
        for (const Lesson& lesson: schedule.getLessons()) {
            orderedSchedule[lesson].push_back(classInfo);
        }
    }

    Schedule newSchedule = schedules[newClassScheduleIndex];
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
 * @details Time complexity: O(c * log s + l * log m + k * d * 2 * log m), where "c" is the number of student's classes not including the old classes' lesson,
 * "s" is the number of schedules, "l" is the number of lessons of the student, "m" is the number of keys of the map,
 * "k" is the number of lessons in the new class, "d" is the number of slots the new lesson fills
 * @param student by reference
 * @param newClass by reference
 * @param auxClass by reference
 * @return True if the Request doesn't conflicts with the Student's Schedule, false otherwise
 */
bool Extractor::isSchedulePossible(const Student& student, const unsigned& newClassScheduleIndex, const Class& auxClass) const {
    map<Lesson, vector<Class>> orderedSchedule;

    for (const Class& classInfo: student.getClasses()) {
        if (classInfo == auxClass) continue;
        const Schedule& schedule = schedules[searchSchedules(classInfo)];
        for (const Lesson& lesson: schedule.getLessons()) {
            orderedSchedule[lesson].push_back(classInfo);
        }
    }

    const Schedule& newSchedule = schedules[newClassScheduleIndex];
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
 * @details Time complexity: O(n)
 * @param classInfo by reference
 * @return True if the Request doesn't conflicts with the Class's balance, false otherwise
 */
bool Extractor::isBalanceMaintained(const unsigned& classScheduleIndex) const {
    int targetSize = schedules[classScheduleIndex].getStudents().size();
    int maximumSize = 0, minimumSize = 41;

    for (const Schedule& schedule: schedules) {
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
 * @details Time complexity: O(n), where "n" is the number of schedules
 * @param classInfo by reference
 * @param auxClass by reference
 * @return True if the Request doesn't conflicts with the Class's balance, false otherwise
 */
bool Extractor::isBalanceMaintained(const unsigned& classScheduleIndex, const unsigned& auxClassScheduleIndex, const Class& auxClass) const {
    int targetSize = schedules[classScheduleIndex].getStudents().size();
    int auxSize = schedules[auxClassScheduleIndex].getStudents().size();
    int maximumSize = 0, minimumSize = 41;

    for (const Schedule& schedule: schedules) {
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
    ofstream record;

    if (!infile.good()) {
        // Create and open Records file
        record = ofstream("../data/records.csv");
        record << "StudentCode,Type,TargetUcCode,TargetClassCode,OldUcCode,OldClassCode" << endl;
    } else record = ofstream("../data/records.csv", ios_base::app);
    infile.close();

    record << request.getStudent().getId() << ',';
    if (request.getType() == "A") record << "Add";
    if (request.getType() == "R") record << "Remove";
    if (request.getType() == "S") record << "Switch";
    record << ',' << request.getTargetClass().getUcCode() << ',' << request.getTargetClass().getClassCode() << ',';
    if (request.getType() != "S") {
        record << "-,-" << endl;
    } else {
        record << request.getAuxClass().getUcCode() << ',' << request.getAuxClass().getClassCode() << endl;
    }
    record.close();
}

/**
 * @brief Function that saves all changes permanently
 * @details Time complexity: O(n * k), where "n" is the number of students and "k" is the number of students' classes
 */
void Extractor::PermanentDataChange() {
    const char* records_txt = "../data/records.csv";
    const char* students_classes_txt = "../data/students_classes.csv";
    ofstream records(records_txt, ios::trunc);
    ofstream students1(students_classes_txt, ios::trunc);
    records << "StudentCode,Type,TargetUcCode,TargetClassCode,OldUcCode,OldClassCode\n";
    students1 << "StudentCode,StudentName,UcCode,ClassCode\n";
    for (Student student: students) {
        for(Class c: student.getClasses())
        students1 << student.getId() << "," << student.getName() << "," << c.getUcCode() << "," << c.getClassCode() << "\n";
    }
    records.close();
    students1.close();

}