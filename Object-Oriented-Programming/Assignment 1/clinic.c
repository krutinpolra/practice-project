/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : KRUTIN BHARATBHAI POLRA
Student ID#: 135416220
Email      : kbpolra@myseneca.ca
Section    : NFF

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, Eligible_Record = 0;

    if (fmt == FMT_TABLE) {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber != 0) {
            displayPatientData(&patient[i], fmt);
            Eligible_Record = 1;
        }
    }

    if (!Eligible_Record) {
        printf("*** No records found ***\n\n");
    }

    printf("\n");
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int select;


    do {

        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");

        select = inputIntRange(0, 2);
        putchar('\n');

        if (select == 1) {

            searchPatientByPatientNumber(patient, max);
            putchar('\n');
            suspend();
        }
        else if (select == 2) {

            searchPatientByPhoneNumber(patient, max);
            putchar('\n');
            suspend();
        }

    } while (select);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int emptyIndex;

    emptyIndex = findPatientIndexByPatientNum(0, patient, max);

    if (emptyIndex != -1) {

        patient[emptyIndex].patientNumber = nextPatientNumber(patient, max);

        printf("Patient Data Input\n"
            "------------------\n"
            "Number: %05d\n", patient[emptyIndex].patientNumber);

        inputPatient(&patient[emptyIndex]);

        printf("*** New patient record added ***\n\n");
    }
    else {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int num = 0, result = 0;

    printf("Enter the patient number: ");

    num = inputIntPositive();

    putchar('\n');

    result = findPatientIndexByPatientNum(num, patient, max);

    if (result != -1) {
        menuPatientEdit(&patient[result]);
    }
    else {
        printf("ERROR: Patient record not found!\n");
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int num = 0, result = 0;
    char select;

    printf("Enter the patient number: ");
    num = inputIntPositive();

    result = findPatientIndexByPatientNum(num, patient, max);
    if (result != -1) {

        putchar('\n');
        displayPatientData(&patient[result], FMT_FORM);

        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");

        select = !(inputCharOption("yn") == 'y');

        if (!select) {

            patient[result].patientNumber = 0;
            strcpy(patient[result].name, "\0");
            strcpy(patient[result].phone.description, "\0");
            strcpy(patient[result].phone.number, "\0");

            printf("Patient record has been removed!\n\n");
        }

        else {

            printf("Operation aborted.\n\n");
        }
    }
    else {

        putchar('\n');
        printf("ERROR: Patient record not found!\n\n");
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
    int i = 0;
    int index = 0;

    displayScheduleTableHeader(NULL, 1);

    sortAppointments(data->appointments, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++) {

        index = findPatientIndexByPatientNum(
            data->appointments[i].patientNumber,
            data->patients, data->maxPatient);

        if (data->appointments[i].patientNumber > 0) {

            displayScheduleData(&data->patients[index],
                &data->appointments[i], 1);
        }
    }
    putchar('\n');
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{

    int  i, index;
    struct Date date = { 0 };
    struct Date* datePtr = &date;

    date = calculateDaysInMonth();
    putchar('\n');

    displayScheduleTableHeader(datePtr, 0);
    sortAppointments(data->appointments, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++) {

        if (date.year == data->appointments[i].date.year
            && date.month == data->appointments[i].date.month
            && date.day == data->appointments[i].date.day) {

            index = findPatientIndexByPatientNum(
                data->appointments[i].patientNumber,
                data->patients, data->maxPatient);

            if (data->appointments[i].patientNumber > 0) {
                displayScheduleData(&data->patients[index],
                    &data->appointments[i], 0);
            }
        }
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment appointments[], int maxAppointments,
    struct Patient patients[], int maxPatients)
{
    int index, patientNum, keepTrying = 0;
    struct Date date = { 0 };
    struct Time time = { 0 };

    index = findAppointmentIndex(0, appointments, maxAppointments);
    if (index != -1) {

        printf("Patient Number: ");
        patientNum = inputIntPositive();

        if (findPatientIndexByPatientNum(patientNum, patients, maxPatients) != -1) {

            while (!keepTrying) {
                date = calculateDaysInMonth();
                time = enterTime();

                if (!checkTimeSlot(date, time, appointments, maxAppointments)) {

                    appointments[index].date = date;
                    appointments[index].time = time;
                    appointments[index].patientNumber = patientNum;
                    keepTrying += 1;

                    putchar('\n');
                    printf("*** Appointment scheduled! ***\n\n");
                }
                else {
                    putchar('\n');
                    printf("ERROR: Appointment timeslot is not available!\n\n");
                }
            }
        }
        else {
            printf("ERROR: Patient record not found!\n\n");
        }
    }
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appointments[], int maxAppointments,
    struct Patient patients[], int maxPatients)
{
    int patientNum, i, patientIndex, match = 0, appIndex = 0;
    char selection;
    struct Date date = { 0 };
    struct Appointment blankApp = { 0 };

    printf("Patient Number: ");
    patientNum = inputIntPositive();

    if (findPatientIndexByPatientNum(patientNum, patients, maxPatients) != -1) {
        date = calculateDaysInMonth();
        putchar('\n');
        patientIndex = findPatientIndexByPatientNum(patientNum, patients, maxPatients);

        for (i = 0; i <= maxAppointments; i++) {

            if (appointments[i].patientNumber == patientNum &&
                appointments[i].date.year == date.year &&
                appointments[i].date.month == date.month &&
                appointments[i].date.day == date.day) {

                appIndex = i;
                match += 1;

            }
        }
        if (match) {
            displayPatientData(&patients[patientIndex], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");
            selection = !(inputCharOption("yn"));

            if (!selection)
            {
                appointments[appIndex] = blankApp;
                putchar('\n');
                printf("Appointment record has been removed!\n\n");
            }
            else {
                printf("Operation aborted.\n\n");
            }
        }
        else {
            printf("ERROR: Appointment record not found!\n\n");
        }
    }
    else {
        printf("ERROR: Patient record not found!\n\n");
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int number = 0, searchResult = 0;

    printf("Search by patient number: ");

    number = inputIntPositive();

    putchar('\n');
    searchResult = findPatientIndexByPatientNum(number, patient, max);

    if (searchResult != -1) {

        displayPatientData(&patient[searchResult], FMT_FORM);
    }
    else {
        printf("*** No records found ***\n");
    }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int recordsFound = 0, i;
    char phone[PHONE_LEN + 1] = { 0 };

    printf("Search by phone number: ");

    inputCString(phone, PHONE_LEN, PHONE_LEN);
    putchar('\n');

    displayPatientTableHeader();

    for (i = 0; i <= max; i++) {

        if (strcmp(patient[i].phone.number, phone) == 0) {

            recordsFound = 1;
            displayPatientData(&patient[i], FMT_TABLE);
        }
    }
    if (!recordsFound) {

        putchar('\n');
        printf("*** No records found ***\n");
    }
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int largestNum = 0, i;

    for (i = 0; i < max; i++) {

        if (patient[i].patientNumber > largestNum) {

            largestNum = patient[i].patientNumber;
        }
    }

    largestNum += 1;

    return largestNum;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int patientIndex, i, flag = 0;

    patientIndex = -1;

    for (i = 0; i < max && !flag; i++) {

        if (patient[i].patientNumber == patientNumber) {
            flag++;
            patientIndex = i;
        }
    }
    return patientIndex;
}

// Find the appointment array index by patient number (returns -1 if not found)
int findAppointmentIndex(int patientNumber,
    const struct Appointment appointments[], int max)
{
    int appointmentIndex, i, flag = 0;

    appointmentIndex = -1;

    for (i = 0; i < max && !flag; i++) {

        if (appointments[i].patientNumber == patientNumber) {
            flag++;
            appointmentIndex = i;
        }
    }
    return appointmentIndex;
}

// Sorts the array of appointments by earliest appointment
void sortAppointments(struct Appointment appointments[], int maxAppointments)
{
    int i = 0, j = 0;
    char str1[20], str2[20];
    struct Appointment temp;

    // Bubble sort the appointments based on date and time strings
    for (i = 0; i < maxAppointments - 1; i++) {

        for (j = 0; j < maxAppointments - i - 1; j++) {

            sprintf(str1, "%.4d%.2d%.2d%.2d%.2d",
                appointments[j].date.year, appointments[j].date.month,
                appointments[j].date.day, appointments[j].time.hour,
                appointments[j].time.min);

            sprintf(str2, "%.4d%.2d%.2d%.2d%.2d",
                appointments[j + 1].date.year, appointments[j + 1].date.month,
                appointments[j + 1].date.day, appointments[j + 1].time.hour,
                appointments[j + 1].time.min);

            if (strcmp(str1, str2) > 0) {
                // Swap the appointments
                temp = appointments[j];
                appointments[j] = appointments[j + 1];
                appointments[j + 1] = temp;
            }
        }
    }
}

//checks provided time slot for availability, returns -1 if timeslot taken
int checkTimeSlot(const struct Date date, const struct Time time,
    const struct Appointment appointments[], int max)
{
    int i = 0, match = 0;
    char str1[20], str2[20];

    for (i = 0; i < max; i++) {

        sprintf(str1, "%.4d%.2d%.2d%.2d%.2d",
            date.year, date.month,
            date.day, time.hour,
            time.min);

        sprintf(str2, "%.4d%.2d%.2d%.2d%.2d",
            appointments[i].date.year, appointments[i].date.month,
            appointments[i].date.day, appointments[i].time.hour,
            appointments[i].time.min);

        if (strcmp(str1, str2) == 0) {
            match++;
        }
    }
    return match;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf("Name  : ");
    inputCString(patient->name, 2, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
    int selection = 0;

    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");

    selection = inputIntRange(1, 4);

    switch (selection) {
    case 1:
        strcpy(phone->description, "CELL");
        break;

    case 2:
        strcpy(phone->description, "HOME");
        break;

    case 3:
        strcpy(phone->description, "WORK");
        break;

    case 4:
        strcpy(phone->description, "TBD");
        break;
    }

    if (selection != 4) {

        putchar('\n');
        printf("Contact: %s\n",
            phone->description);
        printf("Number : ");
        inputNumberString(phone->number, PHONE_LEN);
    }
    else {
        phone->number[0] = '\0';
    }
}

// calculates days in month and returns user inputted date
struct Date calculateDaysInMonth(void)
{
    int leapYear = 0;
    struct Date date = { 0 };

    printf("Year        : ");
    date.year = inputIntPositive();

    printf("Month (%d-%d): ", MIN_MONTH, MAX_MONTH);
    date.month = inputIntRange(MIN_MONTH, MAX_MONTH);

    if ((date.year % 4 == 0 && date.year % 100 != 0) || date.year % 400 == 0) {
        leapYear = 1;
    }

    switch (date.month) {
    case 2:
        date.day = leapYear ? 29 : 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        date.day = 30;
        break;
    default:
        date.day = 31;
        break;
    }
    printf("Day (%d-%d)  : ", MIN_DAYS, date.day);
    date.day = inputIntRange(MIN_DAYS, date.day);

    return date;
}
// gets user input of time min and hours
struct Time enterTime(void)
{
    int keepTrying = 0;
    struct Time time = { 0 };

    while (!keepTrying) {

        printf("Hour (%d-%d)  : ", MIN_HOUR, MAX_HOUR);
        time.hour = inputIntRange(MIN_HOUR, MAX_HOUR);

        printf("Minute (%d-%d): ", MIN_MINUTE, MAX_MINUTE);
        time.min = inputIntRange(MIN_MINUTE, MAX_MINUTE);

        if ((time.hour < START_HOUR || time.hour > END_HOUR ||
            (time.hour == END_HOUR && time.min > 0)) ||
            time.min % APPOINTMENT_INTERVAL != 0) {
            printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n",
                START_HOUR, END_HOUR, APPOINTMENT_INTERVAL);
        }
        else {
            keepTrying = 1;
        }
    }
    return time;
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i, recordStored = 0;

    FILE* fp = fopen(datafile, "r");

    for (i = 0; i < max; i++) {

        if (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]",
            &patients[i].patientNumber, patients[i].name,
            patients[i].phone.description, patients[i].phone.number) >= 3) {

            recordStored++;
        }
    }
    fclose(fp);
    fp = NULL;
    return recordStored;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i, recordStored = 0;

    FILE* fp = fopen(datafile, "r");

    for (i = 0; i < max; i++) {

        if (fscanf(fp, "%d,%d,%d,%d,%d,%d",
            &appoints[i].patientNumber, &appoints[i].date.year,
            &appoints[i].date.month, &appoints[i].date.day,
            &appoints[i].time.hour, &appoints[i].time.min) == 6) {

            recordStored++;
        }
    }
    fclose(fp);
    fp = NULL;
    return recordStored;
}


