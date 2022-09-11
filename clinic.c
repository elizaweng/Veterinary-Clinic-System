/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  :Yi-Hsuan Weng
Student ID#:106800204
Email      :yhweng1@myseneca.ca
Section    :NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

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
// main menu (hub) for application
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
            putchar('\n');
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
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;

    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
        }
    }

    putchar('\n');
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int option;
    int flag = 1;

    do
    {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");

        option = inputIntRange(0, 2);

        putchar('\n');
        if (option == 1)
        {
            searchPatientByPatientNumber(patient, max);
        }
        else if (option == 2)
        {
            searchPatientByPhoneNumber(patient, max);
        }
        else
        {
            flag = 0;
        }
    } while (flag);
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i = 0;
    int emptyCounter = 0;
    int nonEmptyCounter = 0;
    int newNum;
    for (i = 0; i < max; i++)  
    {
        if (emptyCounter == 0)
        {
            if (patient[i].patientNumber == 0)          // find empty record
            {
                newNum = nextPatientNumber(patient, max);
                patient[i].patientNumber = newNum;
                inputPatient(&patient[i]);
                emptyCounter++;
                putchar('\n');
                printf("*** New patient record added ***\n\n");
            }
            else
            {
                nonEmptyCounter++;
            }
        }
    }
    if (nonEmptyCounter == max)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }

}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int userInput;
    int index;
    printf("Enter the patient number: ");
    userInput = inputIntPositive();
    index = findPatientIndexByPatientNum(userInput, patient, max);
    putchar('\n');

    if (index >= 0 && index < max)
    {
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int userInput = 0;
    int i = 0;
    char yOrN = 0;

    printf("Enter the patient number: ");

    userInput = inputIntPositive();
    i = findPatientIndexByPatientNum(userInput, patient, max);

    if (i >= 0 && i < max)
    {
        putchar('\n');
        displayPatientData(&patient[i], FMT_FORM);

        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        yOrN = inputCharOption("yn");

        switch (yOrN)
        {
        case 'y':                                           // safe empty state
            patient[i].patientNumber = 0;
            strcpy(patient[i].name, "\0");
            strcpy(patient[i].phone.description, "\0");
            strcpy(patient[i].phone.number, "\0");

            printf("Patient record has been removed!\n\n");
            break;

        case 'n':
            printf("Operation aborted.\n\n");
            break;
        }
    }
    else
    {
        putchar('\n');
        printf("ERROR: Patient record not found!\n\n");
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i;
    int j;
    int record = 0;

    displayScheduleTableHeader(&data->appointments->date, ALLRECORD);
    sortAppoint(data->appointments, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++)                     //loop maxAppointments
    {
        if (data->appointments[i].patientNum != 0)
        {
            for (j = 0; j < data->maxPatient; j++)                 //loop maxPatient
            {
                if (data->patients[j].patientNumber == data->appointments[i].patientNum)        //check patientNumber is in database
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], ALLRECORD);
                    record++;
                }
            }
        }
    }
    putchar('\n');
    if (record == 0)
    {
        printf("*** No records found ***");
    }
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    searchAppointByDate(data->appointments, data->patients,
        data->maxAppointments, data->maxAppointments);

    putchar('\n');

}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointment, int maxAppointment, struct Patient* patient, int maxPatient)
{
    int i = 0;
    int j = 0;
    int index = 0;          //get the existRecordIndex
    int patientNumInput;
    int emptyCounter = 0;
    int nonEmptyCounter;

    printf("Patient Number: ");
    patientNumInput = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumInput, patient, maxPatient);

    if (index != -1)
    {
        for (i = 0; i < maxAppointment; i++)
        {
            if (emptyCounter == 0)
            {
                if (appointment[i].patientNum == 0)         // find slot with patientNum in appointment array
                {
                    do
                    {
                        nonEmptyCounter = 0;                // initialize no empty slot
                        inputAppointmentData(&appointment[i]);
                        for (j = 0; j < i; j++)
                        {
                            if (appointment[i].date.year == appointment[j].date.year &&
                                appointment[i].date.month == appointment[j].date.month &&
                                appointment[i].date.day == appointment[j].date.day &&
                                appointment[i].time.hour == appointment[j].time.hour &&
                                appointment[i].time.min == appointment[j].time.min)
                            {
                                putchar('\n');
                                printf("ERROR: Appointment timeslot is not available!\n\n");
                                nonEmptyCounter++;
                            }
                        }
                    } while (nonEmptyCounter != 0);         // keep looping until no slot
                    appointment[i].patientNum = patientNumInput;
                    emptyCounter++;
                }
            }
        }
    }
    else
    {
        putchar('\n');
        printf("ERROR: appointment record not found!\n\n");
    }

    if (emptyCounter)               // have slot
    {
        putchar('\n');
        printf("*** Appointment scheduled! ***\n\n");
    }
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appoint, int maxAppoint, struct Patient* patient, int maxPatient)
{
    char selection = 0;
    int i;
    int patientNumberInput = 0;
    int yearInput = 0;
    int monthInput = 0;
    int dayInput = 0;

    int rmAppointmentCount = 0;     // remove appointment counter
    int patIndex = 0;       // existing patient index for struct patient array
    int appIndex = 0;       // existing appointment index for struct appointment array
   

    printf("Patient Number: ");
    patientNumberInput = inputIntPositive();
    patIndex = findPatientIndexByPatientNum(patientNumberInput, patient, maxPatient);

    if (patIndex != -1)      // have record in patient array
    {
        inputYearMonthDay(&yearInput, &monthInput, &dayInput);
        appIndex = findAppointIndexByDate(yearInput, monthInput, dayInput, appoint, maxAppoint);

        for (i = 0; i < maxAppoint; i++)
        {
            if (patient[patIndex].patientNumber == appoint[i].patientNum &&        // making sure information is matching
                appoint[appIndex].date.year == appoint[i].date.year &&
                appoint[appIndex].date.month == appoint[i].date.month &&
                appoint[appIndex].date.day == appoint[i].date.day)
            {
                putchar('\n');
                printf("Name  : %s\n", patient[patIndex].name);
                printf("Number: %05d\n", patient[patIndex].patientNumber);
                printf("Phone : ");
                displayFormattedPhone(patient[patIndex].phone.number);
                printf(" (%s)\n", patient[patIndex].phone.description);

                printf("Are you sure you want to remove this appointment (y,n): ");
                selection = inputCharOption("yn");

                if (selection == 'y')
                {
                    appoint[i].patientNum = 0;      // set to safe empty state
                    appoint[i].date.year = 0;
                    appoint[i].date.month = 0;
                    appoint[i].date.day = 0;
                    appoint[i].time.hour = 0;
                    appoint[i].time.min = 0;
                    rmAppointmentCount++;
                }
                else
                {
                    putchar('\n');
                    printf("Operation aborted.\n\n");
                }
            }
        }
        if (rmAppointmentCount)
        {
            putchar('\n');
            printf("Appointment record has been removed!\n\n");
        }
        else
        {
            putchar('\n');
            printf("ERROR: Appointment record not found!\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int userInput;
    int i;
    printf("Search by patient number: ");
    userInput = inputIntPositive();
    putchar('\n');
    i = findPatientIndexByPatientNum(userInput, patient, max);
    if (i >= 0 && i <= max)                              //If the record is found, the index position of the matched element should be returned.
    {
        displayPatientData(&patient[i], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }

    putchar('\n');
    suspend();
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i;
    char userInput[PHONE_LEN + 1] = { 0 };
    int record = 0;
    int flag = 1;

    printf("Search by phone number: ");
    inputCString(userInput, PHONE_LEN, PHONE_LEN);
    putchar('\n');
    displayPatientTableHeader();
    do
    {
        for (i = 0; i < max; i++)
        {
            if (strcmp(userInput, patient[i].phone.number) == 0)
            {
                displayPatientData(&patient[i], FMT_TABLE);
                record++;
                flag = 0;
            }
        }
        if (record == 0)
        {
            putchar('\n');
            printf("*** No records found ***\n");
            flag = 0;
        }

    } while (flag);


    putchar('\n');
    suspend();
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int nextNum = 0;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > nextNum)
        {
            nextNum = patient[i].patientNumber;

        }
    }
    return nextNum + 1;

}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i = 0;
    int existRecordIndex = 0;
    int matchNum = 0;

    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            existRecordIndex = i;
            matchNum++;
        }
    }

    if (matchNum == 0)                                              //  record can't be located (matched)
    {
        existRecordIndex = -1;                                  //  then -1 should be returned
    }

    return existRecordIndex;
}

//sort the appointment by the time (Bubble Sort)
void sortAppoint(struct Appointment* appoint, int max)
{
    int i;
    int j;
    int currentIndexToMins = 0;
    int nextIndexToMins = 0;
    struct Appointment temp = { 0 };

    for (i = max - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (appoint[j].date.year >= appoint[j + 1].date.year && appoint[j + 1].date.year != 0)
            {
                currentIndexToMins = (appoint[j].date.year * 12 * 30 * 24 * 60) +
                    (appoint[j].date.month * 30 * 24 * 60) +
                    (appoint[j].date.day * 24 * 60) + (appoint[j].time.hour * 60) +
                    (appoint[j].time.min);
                nextIndexToMins = (appoint[j + 1].date.year * 12 * 30 * 24 * 60) +
                    (appoint[j + 1].date.month * 30 * 24 * 60) +
                    (appoint[j + 1].date.day * 24 * 60) + (appoint[j + 1].time.hour * 60) +
                    (appoint[j + 1].time.min);

                if (currentIndexToMins > nextIndexToMins)
                {
                    temp = appoint[j];
                    appoint[j] = appoint[j + 1];
                    appoint[j + 1] = temp;
                }
            }
        }
    }
}

// Check whether year is a leap year
int checkLeapYear(int year)
{
    int result = 0;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        result = 1;
    }

    return result;
}


// Find the appointment array index by date (returns -1 if not found)
int findAppointIndexByDate(int year, int month, int day,
    const struct Appointment appoint[], int max)
{
    int i = 0;
    int existRecordIndex = 0;
    int matchNum = 0;

    for (i = 0; i < max; i++)
    {
        if (year == appoint[i].date.year)
        {
            if (month == appoint[i].date.month)
            {
                if (day == appoint[i].date.day)
                {
                    existRecordIndex = i;
                    matchNum++;
                }
            }
        }
    }

    if (matchNum == 0)                                              //  record can't be located (matched)
    {
        existRecordIndex = -1;                                     //  then -1 should be returned
    }

    return existRecordIndex;
}


// Search the appointment: based on the leap year, month to measure the date
void searchAppointByDate(struct Appointment appoint[], struct Patient patients[],
                         int maxAppointment, int maxPatient)
{
    int i;                        //index for appointmentData
    int j;                        //index for patientData
    int index = 0;                //get the existRecordIndex
    int year = 0;
    int month = 0;
    int day = 0;

    inputYearMonthDay(&year, &month, &day);
    sortAppoint(appoint, maxAppointment);

    index = findAppointIndexByDate(year, month, day, appoint, maxAppointment);

    if (index != -1)                                    // have record
    {
        putchar('\n');
        displayScheduleTableHeader(&appoint[index].date, SPEC_DATE);

        for (i = 0; i < maxAppointment; i++)            //loop maxAppointment
        {
            if (appoint[i].date.year == appoint[index].date.year &&
                appoint[i].date.month == appoint[index].date.month &&
                appoint[i].date.day == appoint[index].date.day)
            {
                for (j = 0; j < maxPatient; j++)        //loop maxPatient
                {
                    if (patients[j].patientNumber == appoint[i].patientNum)
                    {
                        displayScheduleData(&patients[j], &appoint[i], SPEC_DATE);
                    }
                }
            }

        }
    }
    else
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{

    char name[NAME_LEN + 1] = { 0 };
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(name, 1, NAME_LEN);
    putchar('\n');
    strcpy(patient->name, name);
    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    char phoneNumber[PHONE_LEN + 1] = { 0 };
    int phoneType;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    phoneType = inputIntRange(1, 4);

    if (phoneType > 0 && phoneType < 4)
    {
        if (phoneType == 1)
        {
            strcpy(phone->description, "CELL");
        }
        else if (phoneType == 2)
        {
            strcpy(phone->description, "HOME");
        }
        else
        {
            strcpy(phone->description, "WORK");
        }
        putchar('\n');
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputPhoneNumString(phoneNumber, PHONE_LEN);
        strcpy(phone->number, phoneNumber);

    }
    else
    {
        strcpy(phone->description, "TBD");
    }
}

// Get user input for appointment day: check the day of month (specific date)
void inputYearMonthDay(int* year, int* month, int* day)
{
    int yearInput = 0;
    int monthInput = 0;
    int dayInput = 0;
    int leapYear = 0;

    printf("Year        : ");
    yearInput = inputIntPositive();
    leapYear = checkLeapYear(yearInput);
    *year = yearInput;

    printf("Month (1-12): ");
    monthInput = inputIntRange(1, 12);
    *month = monthInput;

    if (monthInput == 1 || monthInput == 3 || monthInput == 5 || monthInput == 7 ||
        monthInput == 8 || monthInput == 10 || monthInput == 12)
    {
        printf("Day (1-%d)  : ", SOL_MONTH_DAYS);
        dayInput = inputIntRange(1, SOL_MONTH_DAYS);

    }
    else if (monthInput == 4 || monthInput == 6 || monthInput == 9 || monthInput == 11)
    {
        printf("Day (1-%d)  : ", LUN_MONTH_DAYS);
        dayInput = inputIntRange(1, LUN_MONTH_DAYS);

    }
    else                                // Feb
    {
        if (leapYear == 1)
        {
            printf("Day (1-%d)  : ", LEAP_FEB_MONTH_DAYS);
            dayInput = inputIntRange(1, LEAP_FEB_MONTH_DAYS);
        }
        else
        {
            printf("Day (1-%d)  : ", NON_LEAP_FEB_MONTH_DAYS);
            dayInput = inputIntRange(1, NON_LEAP_FEB_MONTH_DAYS);
        }
    }
    *day = dayInput;
}

// Get user input for appointment info.
void inputAppointmentData(struct Appointment* appointment)
{
    int year;
    int month;
    int day;
    int hour;
    int minute;

    inputYearMonthDay(&year, &month, &day);

    do
    {
        printf("Hour (0-23)  : ");
        hour = inputIntRange(0, 23);
        printf("Minute (0-59): ");
        minute = inputIntRange(0, 59);

        if (hour < OPENHOUR || hour > CLOSEHOUR || minute % INTERVAL != 0 || (hour == CLOSEHOUR && minute != 0))      // output error message
        {
            printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n",
                OPENHOUR, CLOSEHOUR, INTERVAL);
        }
        else                                                                                                    // store in the appoint. data
        {
            appointment->date.year = year;
            appointment->date.month = month;
            appointment->date.day = day;
            appointment->time.hour = hour;
            appointment->time.min = minute;
        }

    } while (hour < OPENHOUR || hour > CLOSEHOUR || minute % INTERVAL != 0 || (hour == CLOSEHOUR && minute != 0));
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int recs = 0;

    // Get access the data file(patientData)
    FILE* fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (recs < max)
        {
            fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]\n", &patients[recs].patientNumber, patients[recs].name, patients[recs].phone.description, patients[recs].phone.number);
            recs++;
        }
        // clearn up
        fclose(fp);
        fp = NULL;
    }
    // No access
    else
    {
        printf("ERROR: Unable to open %s file!\n\n", datafile);
    }

    return recs;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int recs = 0;
    int field = 6;

    // Get access the data file(appointmentData)
    FILE* fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (recs < max && field == 6)
        {
            field = fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[recs].patientNum, &appoints[recs].date.year,
                &appoints[recs].date.month,&appoints[recs].date.day,&appoints[recs].time.hour, &appoints[recs].time.min);
            if (field == 6)             // only read the line with 6 field
            {
                recs++;
            }
        }
        // clearn up
        fclose(fp);
        fp = NULL;
    }
    // No access
    else
    {
        printf("ERROR: Unable to open %s file!\n\n", datafile);
    }

    return recs;
}