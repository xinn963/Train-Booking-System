#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#pragma warning (disable:4996)

// Staff Module Function
#define M_MAX_SIZE 10
#define S_MAX_SIZE 50
void managerSignup();
void staffSignup();
void sModuleLogin();
void selectFunction();
void profile();
void searchManager(FILE* managerPtr, char* input, int option, int addressOption);
void searchStaff(FILE* staffPtr, char* input, int option, int addressOption);
void sModuleSearch();
void attendance();
void sPasswordRecovery();
void modifyEditTable(int option, char* input, int addressOption);
void sModuleModify();
void sModuleDelete();
void sModuleAdd();
void sModuleDisplay();
bool isValidName(char* name);
bool isValidIC(char* ic);
bool isValidPassword(char* password);
bool isValidAge(char* age);
bool isValidPhone(char* phoneNumber);
bool isValidAddress(char* address);
bool isValidAddress2(char* address2);
bool isValidPostCode(char* postCode);
bool isValidState(char* state);
bool isValidEmail(char* email);
void confirmPassword(char* password, int* wrongConfirm, bool* continueCreation);
void reportMenu();
char logInID[5];
int checkPosition;
typedef struct {
	char question[50];
	char answer[50];
} secure;
secure recovery[5] = {
	{"What is your favourite fruit", ""},
	{"What is the first name of your favourite uncle", ""},
	{"What is your hobby", ""},
	{"What is the name of your favourite book", ""},
	{"Who was your first boss", ""}
};
typedef struct {
	char id[5];
	char name[50];
	char ic[13];
	char age[3];
	char gender;
	char status;
	char phoneNumber[11];
	char email[50];
	char address[100], address2[100], state[50];
	char postCode[6];
	double salary;
	char password[13];
	secure recovery[5];
} management;
typedef struct {
	char id[5];
	char name[50];
	char ic[13];
	char age[3];
	char gender;
	char status;
	char phoneNumber[11];
	char email[50];
	char address[100], address2[100], state[50];
	char postCode[6];
	double salary;
	char password[13];
	secure recovery[5];
	int attend, late, absent, totalDaysAttend; // checkc attendance in today already get or not
	double attendanceRate, lateRate, absentRate;
	char lateReason[1000];
} staffDetails;

// Member Module Functions
#define MAX_SIZE 100
SYSTEMTIME t;
void mModuleLogin();
void mModuleSignup();
void memberSignUp(profile);
void mPasswordRecovery();
void menu(read);
void searchMember();
void modifyMember(read);
void displayMember(read);
void modifyPassword(read);
void modifyRecovery(read);
void readFile(profile);
void deleteMemberMenu(read);
void deleteMember(read);
void staffMenu();
void displayAllMember();
void searchID();
void searchName();
void searchAge();
void searchGender();
void memberActivityLog();
void displayDeleted();
// file pointer
FILE* mFile;
// struct to store member info
typedef struct {
	char q1[20], q2[20], q3[20];
} Answer;
typedef struct {
	char memberID[20], password[30], name[30], gender, email[30], ic[13], phoneNo[11];
	int age;
	Answer recovery;
} MemberInfo;

MemberInfo member;
Answer mRecovery;

//constants
#define MORNING_PEAK_HOUR_START 700
#define MORNING_PEAK_HOUR_END 900
#define EVENING_PEAK_HOUR_START 1700  
#define EVENING_PEAK_HOUR_END 1900
//Train scheduling module functions
void addTrain();
void searchTrain();
void displayTrain();
void modifyTrain();
void deleteTrain();
void reportTrain();
void display();
int morningPeakHour(int time);
int eveningPeakHour(int time);
void scheduleMain();

//structures
typedef struct {
	int day, month, year;
} Date;

typedef struct {
	char trainId[5], trainType[10];
	char departureStation[50], arrivalStation[50];
	Date departureDate;
	int departureTime, arrivalTime;
	int availableSeat;
	double price;
} TrainScheduling;

//Ticket Booking Structure
typedef struct {
	int hour, min;
} Time;

typedef struct {
	Date startDate;
	char departPlace[100];
	char destination[100];
	int noPax;
} Search;

typedef struct {
	Date dateDepAvailable;
	Time timeDepAvailable;
	Time timeDestAvailable;
	int seatStillAvailable;
	double fare;
} ChooseTrain;

typedef struct {
	char receiptId[9];
	//char customerName[30];
	char trainNo[6];
	char trainType[10];
	char departPlace[100];
	char destination[100];
	char paymentMethod[20];
	double paymentAmount;
	Date departDate;
	Time departTime;
	Time arrivalTime;
	Search ticketInfo;
	ChooseTrain trainInfo;
} Payment;

//Ticket Booking Function Prototype
Date selectDate();
int noOfPax();
void selectPlace(char* depPlace);
void selectTrain(char* trainno);
void selectPayment(char* paymentMethod);
void generateRandomReceiptID(char* receiptID, int length);
void printReceipt(Payment receipt);
void addBooking();
void displayBooking();
void modifyBooking();
void deleteBooking();
void reportBooking();
int ticketBookingMenu();

// Staff Module Function
void sModuleMain() {
	int option, select;

	do {
		system("cls");
		printf("Staff Module\n");
		printf("------------------------------\n");
		printf("1. Manager\n");
		printf("2. Staff\n");
		printf("3. Exit\n");
		printf("------------------------------\n");
		printf("Select your position (1-3) : ");
		rewind(stdin);
		scanf("%d", &select);

		if (select >= 1 || select <= 2) {
			system("cls");
			checkPosition = select;
		}
	} while (select < 1 || select > 3);


	if (select == 3) {
		main();
	}

	do {
		system("cls");
		printf("Welcome!\n");
		printf("------------------------------\n");
		printf("1. Sign up\n");
		printf("2. Log in\n");
		printf("3. Back\n");
		printf("------------------------------\n");
		printf("Select your option (1-3) : ");
		rewind(stdin);
		scanf("%d", &option);
	} while (option < 1 || option > 3);


	if (select == 1 && option == 1) {
		managerSignup();
	}
	else if (select == 2 && option == 1) {
		staffSignup();
	}
	else if (option == 3) {
		sModuleMain();
	}
	else {
		sModuleLogin();
	}
}

void managerSignup() {
	system("cls");

	FILE* managerPtr, * staffPtr;
	managerPtr = fopen("managerFile.bin", "ab+");
	staffPtr = fopen("staffFile.bin", "rb");
	if (managerPtr == NULL || staffPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	management manager, temporary;
	staffDetails staff;

	char managerID[5] = "M001";
	int i = 0;
	int checkIC = 0;
	int count = 0;  //Counter for the number of managers
	int wrongConfirm = 0;
	bool continueCreation = true;

	do {
		fread(&manager, sizeof(management), 1, managerPtr);
		if (strcmp(manager.id, managerID) == 0) {
			if (managerID[3] == '9') {
				managerID[3] = '0';
				managerID[2]++;
				i++;
				count++;
			}
			else {
				managerID[3]++;
				i++;
				count++;
			}
		}
		else {
			break;
		}
	} while (i < M_MAX_SIZE);

	if (count >= M_MAX_SIZE) {
		printf("Maximum number of manager accounts (%d) has already been reached.\n", M_MAX_SIZE);
		system("pause");
		sModuleMain();
	}

	printf("Sign Up: Manager Profile\n");
	printf("-------------------------------------------\n");


	do {
		printf("Name (X to Exit): ");
		rewind(stdin);
		scanf(" %[^\n]", manager.name);
		if (strcmp(manager.name, "X") == 0 || strcmp(manager.name, "x") == 0) {
			sModuleMain();
		}
		if (!isValidName(manager.name)) {
			printf("\nInvalid Name (No Special Character or Number)\n\n");
			system("pause");
			managerSignup();
		}
	} while (!isValidName(manager.name));


	do {
		printf("IC		: ");
		scanf("%s", manager.ic);
		while (!isValidIC(manager.ic)) {
			printf("\nInvalid IC\n");
			printf("1. IC must have 12 characters\n2. Ensure first 6 character is valid year, month and day\n\n");
			printf("IC		: ");
			rewind(stdin);
			scanf("%s", manager.ic);
		}

		rewind(managerPtr);
		checkIC = 1; // Assume the IC is unique until proven otherwise
		while (fread(&temporary, sizeof(management), 1, managerPtr) != 0) {
			if (strcmp(temporary.ic, manager.ic) == 0) {
				printf("This IC is already registered\n");
				checkIC = 0;
				break;
			}
		}

		rewind(staffPtr);
		while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
			if (strcmp(staff.ic, manager.ic) == 0) {
				printf("This IC is already registered\n");
				checkIC = 0;
				break;
			}
		}

	} while (!checkIC);


	do {
		printf("Age		: ");
		rewind(stdin);
		scanf("%s", &manager.age);
		if (!isValidAge(manager.age)) {
			printf("Not meeting the entry age (18-45)\n");
		}
	} while (!isValidAge(manager.age));


	if (manager.ic[11] % 2 != 0) {
		manager.gender = 'M'; // Odd digit indicates male
	}
	else if (manager.ic[11] % 2 == 0) {
		manager.gender = 'F'; // Even digit indicates female
	}

	manager.status = 'F';

	do {
		printf("Phone Number	: ");
		rewind(stdin);
		scanf("%s", &manager.phoneNumber);
		if (!isValidPhone(manager.phoneNumber)) {
			printf("Invalid Phone Number\n");
		}
	} while (!isValidPhone(manager.phoneNumber));


	do {
		printf("Email		: ");
		rewind(stdin);
		scanf(" %[^\n]", manager.email);
		if (!isValidEmail(manager.email)) {
			printf("Invalid Email\n");
		}
	} while (!isValidEmail(manager.email));


	do {
		printf("Address line 1	: ");
		rewind(stdin);
		scanf(" %[^\n]", manager.address);
		if (!isValidAddress(manager.address)) {
			printf("Invalid Address Line 1\n");
		}
	} while (!isValidAddress(manager.address));


	do {
		printf("Address line 2	: ");
		rewind(stdin);
		scanf(" %[^\n]", &manager.address2);
		if (!isValidAddress2(manager.address2)) {
			printf("Invalid Address Line 2\n");
		}
	} while (!isValidAddress2(manager.address2));


	do {
		printf("Postal code	: ");
		rewind(stdin);
		scanf("%s", &manager.postCode);
		if (!isValidPostCode(manager.postCode)) {
			printf("Invalid Postal Code\n");
		}
	} while (!isValidPostCode(manager.postCode));


	do {
		printf("State		: ");
		rewind(stdin);
		scanf(" %[^\n]", &manager.state);
		if (!isValidState(manager.state)) {
			printf("Invalid State\n");
		}
	} while (!isValidState(manager.state));
	printf("\n");


	manager.salary = 10000.00;


	system("pause");
	system("cls");
	printf("In case you forget your password...\n");
	printf("------------------------------------------------------------------\n");
	for (int j = 0; j < 5; j++) {
		printf("Question %d	: %s ?\n", j + 1, recovery[j].question);
		printf("Ans		: ");
		rewind(stdin);
		scanf(" %[^\n]", manager.recovery[j].answer);
		printf("\n");
	}

	system("pause");
	do {
		system("cls");
		printf("Sign Up: Manager Profile\n");
		printf("-------------------------------------------\n");
		printf("Create Password		: ");
		rewind(stdin);
		scanf(" %[^\n]", &manager.password);

		if (!isValidPassword(manager.password)) {
			printf("\n\nInvalid Password\n");
			printf("Note : Ensure password is between 8 and 12 characters long and does not contain spaces.\n\n");
		}
		else {
			confirmPassword(manager.password, &wrongConfirm, &continueCreation); // Pass continueCreation by reference
		}
		printf("\n");
		system("pause");
	} while (!isValidPassword(manager.password) || !continueCreation);


	printf("\n\n");
	printf("Process successful\n");
	time_t t = time(NULL);
	struct tm date = *localtime(&t);
	printf("Signup in %d-%02d-%02d %02d:%02d\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min);
	printf("Thank you %s, this is your id : %s\n\n", manager.name, managerID);
	strcpy(manager.id, managerID);
	fwrite(&manager, sizeof(management), 1, managerPtr);

	fclose(managerPtr);
	fclose(staffPtr);

	system("pause");
	system("cls");
	sModuleMain();
}

void staffSignup() {
	system("cls");
	FILE* staffPtr, * managerPtr, * writePtr;
	staffPtr = fopen("staffFile.bin", "rb");
	managerPtr = fopen("managerFile.bin", "rb");
	if (staffPtr == NULL || managerPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	staffDetails* staff = malloc(S_MAX_SIZE * sizeof(staffDetails));
	if (staff == NULL) {
		printf("Memory allocation failed\n");
		return;
	}

	staffDetails check;
	management manager;


	char staffID[5] = "S001";

	int i = 0;
	int j = 0;
	int checkIC = 0;
	int self = 0;
	int recordS = 0;
	char temporaryID[6];
	int temporarySelf = -1;
	int count = 0;  //Counter for the number of staff
	int wrongConfirm = 0;
	bool continueCreation = true;

	for (int i = 0; i < S_MAX_SIZE; i++) {
		if (fread(&staff[i], sizeof(staffDetails), 1, staffPtr) != 0) {
			if (strcmp(staff[i].id, staffID) == 0 && strcmp(staff[i].name, "DEL") == 0) {
				self = i;
				temporarySelf = self;
				strcpy(temporaryID, staffID);
				count++;
				if (staffID[3] == '9') {
					staffID[3] = '0';
					staffID[2]++;
				}
				else {
					staffID[3]++;
				}
			}
			else if (strcmp(staff[i].id, staffID) == 0) {
				if (staffID[3] == '9') {
					staffID[3] = '0';
					staffID[2]++;
				}
				else {
					staffID[3]++;
				}
				recordS++;
				count++;
			}
			else {
				self = i;
				recordS++;
				break;
			}
		}
		else {
			self = i;
			recordS++;
			break;
		}
	}


	if (count >= S_MAX_SIZE) {
		printf("Maximum number of staff accounts (%d) has already been reached.\n", S_MAX_SIZE);
		system("pause");
		sModuleMain();
	}


	if (temporarySelf >= 0) {
		self = temporarySelf;
	}


	do {
		system("cls");
		printf("Sign Up: Staff Profile\n");
		printf("-------------------------------------------\n");
		printf("Name (X to Exit): ");
		rewind(stdin);
		scanf(" %[^\n]", staff[self].name);
		if (strcmp(staff[self].name, "X") == 0 || strcmp(staff[self].name, "x") == 0) {
			sModuleMain();
		}
		if (!isValidName(staff[self].name)) {
			printf("\nInvalid Name (No Special Character or Number)\n");
			system("pause");
		}
	} while (!isValidName(staff[self].name));


	do {
		printf("IC		: ");
		scanf("%s", staff[self].ic);
		while (!isValidIC(staff[self].ic)) {
			printf("\nInvalid IC\n");
			printf("1. IC must have 12 characters\n2. Ensure first 6 character is valid year, month and day\n\n");
			printf("IC		: ");
			rewind(stdin);
			scanf("%s", staff[self].ic);
		}


		rewind(staffPtr);
		checkIC = 1; // Assume the IC is unique until proven otherwise
		while (fread(&check, sizeof(staffDetails), 1, staffPtr) != 0) {
			if (strcmp(check.ic, staff[self].ic) == 0) {
				printf("This IC is already registered\n");
				checkIC = 0;
				break;
			}
		}

		rewind(managerPtr);
		while (fread(&manager, sizeof(management), 1, managerPtr) != 0) {
			if (strcmp(manager.ic, staff[self].ic) == 0) {
				printf("This IC is already registered\n");
				checkIC = 0;
				break;
			}
		}
	} while (!checkIC);

	fclose(staffPtr);
	fclose(managerPtr);


	do {
		printf("Age		: ");
		rewind(stdin);
		scanf("%s", &staff[self].age);
		if (!isValidAge(staff[self].age)) {
			printf("Not meeting the entry age (18-45)\n");
		}
	} while (!isValidAge(staff[self].age));


	if (staff[self].ic[11] % 2 != 0) {
		staff[self].gender = 'M'; // Odd digit indicates male
	}
	else if (staff[self].ic[11] % 2 == 0) {
		staff[self].gender = 'F'; // Even digit indicates female
	}

	do {
		printf("Status (F/P)	: ");
		rewind(stdin);
		scanf("%c", &staff[self].status);
		staff[self].status = toupper(staff[self].status);
		if (staff[self].status != 'F' && staff[self].status != 'P') {
			printf("Invalid Status (F)Full-time or (P)Part-time\n");
		}
	} while (staff[self].status != 'F' && staff[self].status != 'P');


	do {
		printf("Phone Number	: ");
		rewind(stdin);
		scanf("%s", &staff[self].phoneNumber);
		if (!isValidPhone(staff[self].phoneNumber)) {
			printf("Invalid Phone Number\n");
		}
	} while (!isValidPhone(staff[self].phoneNumber));


	do {
		printf("Email		: ");
		rewind(stdin);
		scanf(" %[^\n]", staff[self].email);
		if (!isValidEmail(staff[self].email)) {
			printf("Invalid Email\n");
		}
	} while (!isValidEmail(staff[self].email));


	do {
		printf("Address Line 1	: ");
		rewind(stdin);
		scanf(" %[^\n]", staff[self].address);
		if (!isValidAddress(staff[self].address)) {
			printf("Invalid Address Line 1\n");
		}
	} while (!isValidAddress(staff[self].address));


	do {
		printf("Address Line 2	: ");
		rewind(stdin);
		scanf(" %[^\n]", staff[self].address2);
		if (!isValidAddress2(staff[self].address2)) {
			printf("Invalid Address Line 2\n");
		}
	} while (!isValidAddress2(staff[self].address2));


	do {
		printf("Postal code	: ");
		rewind(stdin);
		scanf("%s", &staff[self].postCode);
		if (!isValidPostCode(staff[self].postCode)) {
			printf("Invalid Postal Code\n");
		}
	} while (!isValidPostCode(staff[self].postCode));


	do {
		printf("State		: ");
		rewind(stdin);
		scanf(" %[^\n]", &staff[self].state);
		if (!isValidState(staff[self].state)) {
			printf("Invalid State\n");
		}
	} while (!isValidState(staff[self].state));
	printf("\n");

	staff[self].salary = 3000.00;
	staff[self].attend = 0;
	staff[self].late = 0;
	staff[self].absent = 0;
	staff[self].totalDaysAttend = 0;
	staff[self].attendanceRate = 0;
	staff[self].lateRate = 0;
	staff[self].absentRate = 0;
	strcpy(staff[self].lateReason, "no");

	system("pause");
	system("cls");
	printf("In case you forget your password...\n");
	printf("------------------------------------------------------------------\n");
	for (int j = 0; j < 5; j++) {
		printf("Question %d	: %s ?\n", j + 1, recovery[j].question);
		printf("Ans		: ");
		rewind(stdin);
		scanf(" %[^\n]", staff[self].recovery[j].answer);
		printf("\n");
	}

	system("pause");
	do {
		system("cls");
		printf("Sign Up: Staff Profile\n");
		printf("-------------------------------------------\n");
		printf("Create Password		: ");
		rewind(stdin);
		scanf(" %[^\n]", &staff[self].password);

		if (!isValidPassword(staff[self].password)) {
			printf("Invalid Password\n");
			printf("Note : Ensure password is between 8 and 12 characters long and does not contain spaces.\n\n");
			system("pause");
		}
		else {
			confirmPassword(staff[self].password, &wrongConfirm, &continueCreation); // Pass continueCreation by reference
		}
	} while (!isValidPassword(staff[self].password) || !continueCreation);


	if (temporarySelf >= 0) {
		strcpy(staff[self].id, temporaryID);
	}
	else {
		strcpy(staff[self].id, staffID);
	}

	printf("\n\n");
	printf("Process successful\n");
	time_t t = time(NULL);
	struct tm date = *localtime(&t);
	printf("Signup in %d-%02d-%02d %02d:%02d\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min);
	printf("Thank you %s, this is your id %s\n\n", staff[self].name, staff[self].id);


	writePtr = fopen("staffFile.bin", "wb");
	if (writePtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}


	for (int i = 0; i < recordS; i++) {
		fwrite(&staff[i], sizeof(staffDetails), 1, writePtr);
	}
	fclose(writePtr);
	free(staff); // Free dynamically allocated memory
	system("pause");
	sModuleMain();
}

void sModuleLogin() {
	system("cls");
	FILE* managerPtr, * staffPtr, * writePtr;

	management* manager = malloc(M_MAX_SIZE * sizeof(management));
	if (manager == NULL) {
		printf("Memory allocation failed\n");
		return;
	}

	staffDetails* staff = malloc(S_MAX_SIZE * sizeof(staffDetails));
	if (staff == NULL) {
		printf("Memory allocation failed\n");
		free(manager); // Free memory before returning
		return;
	}

	staffDetails* temporaryS = malloc(S_MAX_SIZE * sizeof(staffDetails));
	if (temporaryS == NULL) {
		printf("Memory allocation failed\n");
		free(manager); // Free memory before returning
		free(staff);   // Free memory before returning
		return;
	}

	char id[5], password[13];
	int option = 0;
	int decide = 0; //check if enter haven't create id want enter again other id or go sign up
	int j = 0;
	int recordS = 0;
	int loginSuccess = 0;
	int validID = 0;
	int found = 0;
	int foundID = 0; // if id haven't create
	int checkHaveID = 0;
	int changePassword = 0;
	int wrongConfirm = 0;
	bool continueCreation = true;
	int self = 0;

	printf("Welcome to the Login Page!\n");
	printf("--------------------------------\n");

	do {
		validID = 0;
		printf("Enter ID	: ");
		scanf("%s", id);
		id[0] = toupper(id[0]);
		strcpy(logInID, "");
		strcpy(logInID, id);


		if ((checkPosition == 1 && id[0] != 'M') || (checkPosition == 2 && id[0] != 'S') || strlen(id) < 4) {
			printf("\nInvalid ID\n");
			if (checkPosition == 1 && id[0] == 'S') {
				printf("You are logging in as a manager (M___)\n\n");
			}
			else if (checkPosition == 2 && id[0] == 'M') {
				printf("You are logging in as a staff member (S___)\n\n");
			}

			do {
				printf("1. Enter again\n");
				printf("2. Exit\n");
				printf("Select your option (1-2) : ");
				rewind(stdin);
				scanf("%d", &option);
				printf("\n");
			} while (option != 1 && option != 2);

			if (option == 2) {
				sModuleMain();
			}
		}
		else {
			validID = 1; // Set isValidID flag to indicate a valid ID
		}
	} while (!validID);

	managerPtr = fopen("managerFile.bin", "rb");
	staffPtr = fopen("staffFile.bin", "rb");
	if (managerPtr == NULL || staffPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	if (id[0] == 'M') {
		while (fread(&manager[checkHaveID].id, sizeof(management), 1, managerPtr) != 0) {
			if (strcmp(manager[checkHaveID].id, id) == 0) {
				foundID++;
				self = checkHaveID;
				break;
			}
			else {
				checkHaveID++;
			}
		}
	}
	else {
		while (fread(&staff[checkHaveID].id, sizeof(staffDetails), 1, staffPtr) != 0) {
			if (strcmp(staff[checkHaveID].id, id) == 0 && strcmp(staff[checkHaveID].name, "DEL") != 0) {
				foundID++;
				self = checkHaveID;
				break;
			}
			else {
				checkHaveID++;
			}
		}
	}

	fclose(managerPtr);
	fclose(staffPtr);


	if (!foundID) {
		system("cls");
		printf("This ID havent Sign up\n\n");
		do {
			printf("1. Enter again\n");
			printf("2. Sign Up\n");
			printf("3. Exit\n");
			printf("Select your option (1-3) : ");
			rewind(stdin);
			scanf("%d", &decide);
			printf("\n");
			if (decide == 1) {
				sModuleLogin();
			}
			else if (decide == 2) {
				if (id[0] == 'M') {
					managerSignup();
				}
				else {
					staffSignup();
				}
			}
			else {
				sModuleMain();
			}
		} while (decide != 1 && decide != 3);
	}


	while (!loginSuccess) {
		printf("Enter password	: ");
		rewind(stdin);
		scanf(" %[^\n]", &password);
		printf("\n");

		managerPtr = fopen("managerFile.bin", "rb");
		staffPtr = fopen("staffFile.bin", "rb");
		if (managerPtr == NULL || staffPtr == NULL) {
			printf("Unable to open the file\n");
			return;
		}

		recordS = 0;
		rewind(staffPtr);
		while (fread(&staff[recordS], sizeof(staffDetails), 1, staffPtr) != 0) {
			recordS++;
		}


		if (id[0] == 'M') {
			rewind(managerPtr);
			for (int i = 0; i < M_MAX_SIZE; i++) {
				fread(&manager[i], sizeof(management), 1, managerPtr);
				if (strcmp(manager[i].id, id) == 0 && strcmp(manager[i].password, password) == 0) {
					found = 1;
					strcpy(logInID, "");
					strcpy(logInID, manager[i].id);
					loginSuccess++;
					break;
				}
				else if (strcmp(manager[i].id, id) == 0 && strcmp(manager[i].password, password) != 0) {
					found = 1;
					do {
						printf("Wrong password\n");
						printf("1. Enter again\n");
						printf("2. Forgot password\n");
						printf("3. Exit\n");
						printf("Select your option (1-3) : ");
						rewind(stdin);
						scanf("%d", &option);
						printf("\n");
						if (option < 1 || option > 3) {
							printf("\nInvalid Option\n");
						}
					} while (option < 1 || option > 3);

					if (option == 1) {
						break;
					}
					else {
						loginSuccess++;
					}
				}
			}

		}

		else if (id[0] == 'S') {
			rewind(staffPtr);
			for (int i = 0; i < recordS; i++) {
				fread(&temporaryS[i], sizeof(staffDetails), 1, staffPtr);
				if (strcmp(temporaryS[i].id, id) == 0 && strcmp(temporaryS[i].password, password) == 0) {
					found = 1;
					if (strcmp(temporaryS[i].recovery[j].answer, "") == 0) {
						system("cls");
						printf("You need set up password recovery answer first\n");
						printf("----------------------------------------------------\n");
						for (int j = 0; j < 5; j++) {
							printf("Question %d	: %s ?\n", j + 1, recovery[j].question);
							printf("Ans		: ");
							rewind(stdin);
							scanf(" %[^\n]", temporaryS[i].recovery[j].answer);
							strcpy(staff[i].recovery[j].answer, temporaryS[i].recovery[j].answer);
							printf("\n");
						}
						printf("Process Successful\n");
						printf("You can change your password in modify mode\n");
						system("pause");
						loginSuccess++;
					}
					else {
						strcpy(logInID, "");
						strcpy(logInID, temporaryS[i].id);
						loginSuccess++;
					}
					break;
				}
				else if (strcmp(temporaryS[i].id, id) == 0 && strcmp(temporaryS[i].password, password) != 0) {
					found = 1;
					if (strcmp(temporaryS[i].recovery[j].answer, "") == 0) {
						printf("You can try enter your IC in your password\n");
						break;
					}
					else {
						do {
							printf("Wrong password\n");
							printf("1. Enter again\n");
							printf("2. Forgot password\n");
							printf("3. Exit\n");
							printf("Select your option (1-3) : ");
							rewind(stdin);
							scanf("%d", &option);
							printf("\n");
							if (option < 1 || option > 3) {
								printf("\nInvalid Option\n");
							}
						} while (option < 1 || option > 3);

						if (option == 1) {
							break;
						}
						else {
							loginSuccess++;
						}
					}
				}
			}
		}
	}

	if (!found) {
		printf("No Found\n");
	}

	fclose(managerPtr);
	fclose(staffPtr);


	if (id[0] == 'S') {
		writePtr = fopen("staffFile.bin", "wb");
		int o = 0;
		for (int s = 0; s < recordS; s++) {
			fwrite(&staff[s], sizeof(staffDetails), 1, writePtr);
		}
		fclose(writePtr);
	}


	free(manager); // Free dynamically allocated memory for manager
	free(staff);   // Free dynamically allocated memory for staff
	free(temporaryS);   // Free dynamically allocated memory for staff
	if (loginSuccess && option == 2) {
		sPasswordRecovery();
	}
	else if (loginSuccess && option == 3) {
		sModuleMain();
	}
	else {
		selectFunction();
	}
	sModuleLogin(); // after passsword recovery can go back here, if no write this will end the program
}

void selectFunction() {
	system("cls");
	int select;
	char id[5];
	strcpy(id, logInID);
	if (id[0] == 'M') {
		do {
			system("cls");
			printf("Select the function\n");
			printf("--------------------------------------------\n");
			printf("1.  Add\n");
			printf("2.  Modify\n");
			printf("3.  Search\n");
			printf("4.  Display\n");
			printf("5.  Delete\n");
			printf("6.  Attendance\n");
			printf("7.  User Profile\n");
			printf("8.  Train Report\n");
			printf("9.  Member Info\n");
			printf("10. Manage Train Schedule\n");
			printf("11. Exit\n");
			printf("--------------------------------------------\n");
			printf("Select your option (1-11) : ");
			rewind(stdin);
			scanf("%d", &select);
			printf("\n");
		} while (select < 1 || select > 11);
		switch (select) {
		case 1:
			sModuleAdd();
			break;
		case 2:
			sModuleModify();
			break;
		case 3:
			sModuleSearch();
			break;
		case 4:
			sModuleDisplay();
			break;
		case 5:
			sModuleDelete();
			break;
		case 6:
			attendance();
			break;
		case 7:
			profile();
			break;
		case 8:
			reportMenu();
			break;
		case 9:
			staffMenu();
			break;
		case 10:
			scheduleMain();
			break;
		case 11:
			sModuleMain();
			break;
		}
	}

	else {
		do {
			system("cls");
			printf("Select the function\n");
			printf("--------------------------------------------\n");
			printf("1. Attendance\n");
			printf("2. Modify\n");
			printf("3. User Profile\n");
			printf("4. Member Info\n");
			printf("5. Manage Train Schedule\n");
			printf("6. Exit\n");
			printf("--------------------------------------------\n");
			printf("Select your option (1-6) : ");
			rewind(stdin);
			scanf("%d", &select);
			printf("\n");
		} while (select < 1 || select > 6);
		switch (select) {
		case 1:
			attendance();
			break;
		case 2:
			sModuleModify();
			break;
		case 3:
			profile();
			break;
		case 4: 
			staffMenu();
			break;
		case 5:
			scheduleMain();
			break;
		case 6:
			sModuleMain();
			break;
		}
	}
}

void reportMenu() {
	int option;
	do {
		system("cls");
		printf("Select a report\n");
		printf("-----------------------------\n");
		printf("1. Train report\n");
		printf("2. Booking report\n");
		printf("3. Exit\n");
		printf("-----------------------------\n");
		printf("Select an option: ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 3) {
			rewind(stdin);
			option = 0;
		}

		switch (option) {
		case 1: reportTrain(); break;
		case 2: reportBooking(); break;
		case 3: selectFunction(); break;
		default: printf("Invalid option...\n"); system("pause");
		}
	} while (1);
}

void sPasswordRecovery() {
	FILE* managerPtr, * staffPtr;
	managerPtr = fopen("managerFile.bin", "rb");
	staffPtr = fopen("staffFile.bin", "rb");

	if (managerPtr == NULL || staffPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	management* manager = malloc(M_MAX_SIZE * sizeof(management));
	if (manager == NULL) {
		printf("Memory allocation failed\n");
		fclose(managerPtr); // Close the file before returning
		fclose(staffPtr);   // Close the file before returning
		return;
	}

	staffDetails* staff = malloc(S_MAX_SIZE * sizeof(staffDetails));
	if (staff == NULL) {
		printf("Memory allocation failed\n");
		fclose(managerPtr); // Close the file before returning
		fclose(staffPtr);   // Close the file before returning
		free(manager);     // Free memory before returning
		return;
	}

	int self = 0;
	int recordM = 0, recordS = 0;
	int correct = 0;
	int option = 0;
	int select;
	int wrongConfirm = 0;
	bool continueCreation = true;
	char temporary[13] = "";
	char id[5], answer[50];
	strcpy(id, logInID);


	if (id[0] == 'M') {
		while (fread(&manager[recordM], sizeof(management), 1, managerPtr) != 0) {
			if (strcmp(manager[recordM].id, id) == 0) {
				self = recordM;
			}
			recordM++;
		}
	}
	else {
		while (fread(&staff[recordS], sizeof(staffDetails), 1, staffPtr) != 0) {
			if (strcmp(staff[recordS].id, id) == 0) {
				self = recordS;
			}
			recordS++;
		}
	}


	fclose(managerPtr);
	fclose(staffPtr);


	do {
		system("cls");
		printf("Password Recovery Question\n");
		printf("--------------------------------------\n");
		correct = 0;
		for (int j = 0; j < 5; j++) {
			printf("Question %d  : %s ?\n", j + 1, recovery[j].question);
			printf("Answer 	    : ");
			rewind(stdin);
			scanf(" %[^\n]", answer);

			if (strcmp(manager[self].recovery[j].answer, answer) == 0 || strcmp(staff[self].recovery[j].answer, answer) == 0) {
				printf("Correct!\n\n");
				correct++;
				if (correct == 3) {
					printf("Authentication successful!\n");
					if (id[0] == 'M') {
						printf("Your password is : %s\n\n", manager[self].password);
					}
					else {
						printf("Your password is : %s\n\n", staff[self].password);
					}
					system("pause");
					do {
						system("cls");
						printf("Would you like to change your password ?\n");
						printf("1. Yes\n2. No\nSelect your option : ");
						rewind(stdin);
						scanf("%d", &option);
						if (option == 2) {
							sModuleLogin();
						}
						printf("\n");
					} while (option != 1 && option != 2);

					if (option == 1) {
						do {
							system("cls");
							printf("Change Password\n");
							printf("-----------------------------------------\n");
							printf("Enter New Password	: ");
							rewind(stdin);
							if (id[0] == 'M') {
								scanf(" %[^\n]", manager[self].password);
								strcpy(temporary, manager[self].password);
							}
							else {
								scanf(" %[^\n]", staff[self].password);
								strcpy(temporary, staff[self].password);
							}

							if (!isValidPassword(temporary)) {
								printf("Invalid Password\n");
								printf("Note : Ensure password is between 8 and 12 characters long and does not contain spaces.\n\n");
							}
							else {
								confirmPassword(temporary, &wrongConfirm, &continueCreation); // Pass continueCreation by reference
								if (continueCreation) {
									printf("\nProcess Succesful\n");
								}
							}
							system("pause");
						} while (!isValidPassword(temporary) || !continueCreation);	//if no use temporary need write many while (!isValidPassword(manager[self].password) || !isValidPassword(staff[self].password));		
					}
					break;
				}
			}
			else {
				printf("Wrong\n\n");
			}
		}
		if (correct < 3) {
			do {
				printf("Authentication failed. Would you like to try again?\n");
				printf("1. Yes\n2. No\nSelect your option: ");
				rewind(stdin);
				scanf("%d", &select);
				printf("\n");
				if (select == 2) {
					sModuleMain();
				}
			} while (select < 1 || select > 2);

		}
	} while (correct < 3 && select == 1); // Repeat if correct is less than 3 and option is 1



	if (id[0] == 'M' && option == 1) {
		managerPtr = fopen("managerFile.bin", "wb");
		if (managerPtr == NULL) {
			printf("Unable to open the file\n");
			return;
		}
		for (int i = 0; i < recordM; i++) {
			fwrite(&manager[i], sizeof(management), 1, managerPtr);
		}
		fclose(managerPtr);
	}
	else if (id[0] == 'S' && option == 1) {
		staffPtr = fopen("staffFile.bin", "wb");
		if (staffPtr == NULL) {
			printf("Unable to open the file\n");
			return;
		}
		for (int i = 0; i < recordS; i++) {
			fwrite(&staff[i], sizeof(staffDetails), 1, staffPtr);
		}
		fclose(staffPtr);
	}
	// Free allocated memory
	free(manager);
	free(staff);
}

void profile() {
	system("cls");
	FILE* managerPtr, * staffPtr;
	managerPtr = fopen("managerFile.bin", "rb");
	staffPtr = fopen("staffFile.bin", "rb");
	if (managerPtr == NULL || staffPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	management manager;
	staffDetails staff;
	char id[5];
	int option;
	strcpy(id, logInID);

	printf("Profile Information\n======================================\n");

	if (id[0] == 'M') {
		while (fread(&manager, sizeof(management), 1, managerPtr) != 0) {
			if (strcmp(manager.id, id) == 0) {
				printf("ID		: %s\n", manager.id);
				printf("Name		: %s\n", manager.name);
				printf("IC		: %s\n", manager.ic);
				printf("Age		: %s\n", manager.age);
				printf("Gender		: %c\n", manager.gender);
				printf("Phone Number	: %s\n", manager.phoneNumber);
				printf("Email		: %s\n", manager.email);
				printf("Address Line 1	: %s\n", manager.address);
				printf("Address Line 2	: %s\n", manager.address2);
				printf("Postal Code	: %s\n", manager.postCode);
				printf("State		: %s\n", manager.state);
				printf("Salary		: RM%.2f\n", manager.salary);
				break;
			}
		}
	}
	else {
		while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
			if (strcmp(staff.id, id) == 0) {
				printf("ID		: %s\n", staff.id);
				printf("Name		: %s\n", staff.name);
				printf("IC		: %s\n", staff.ic);
				printf("Age		: %s\n", staff.age);
				printf("Gender		: %c\n", staff.gender);
				printf("Phone Number	: %s\n", staff.phoneNumber);
				printf("Email		: %s\n", staff.email);
				printf("Address Line 1	: %s\n", staff.address);
				printf("Address Line 2	: %s\n", staff.address2);
				printf("Postal Code	: %s\n", staff.postCode);
				printf("State		: %s\n", staff.state);
				printf("Salary		: RM%.2f\n", staff.salary);
				break;
			}
		}
	}

	fclose(managerPtr);
	fclose(staffPtr);

	do {
		printf("\n\n\n\nDo you want modify your profile ?\n-------------------------------------\n");
		printf("1. Yes\n2. No\n-------------------------------------\nSelect your option (1-2) : ");
		rewind(stdin);
		scanf("%d", &option);
	} while (option < 1 || option > 2);

	if (option == 1) {
		sModuleModify();
	}
	else {
		selectFunction();
	}
}

void searchManager(FILE* managerPtr, char* input, int option, int addressOption) {
	management manager;
	int found = 0;
	int j = 0; //to display manager title one time
	char temporary[100] = "";
	char temp = ' ';

	while (fread(&manager, sizeof(management), 1, managerPtr) != 0) {
		switch (option) {
		case 1:
			strcpy(temporary, manager.name);
			break;
		case 2:
			strcpy(temporary, manager.phoneNumber);
			break;
		case 3:
			if (addressOption == 1) {
				strcpy(temporary, manager.address);
			}
			else if (addressOption == 2) {
				strcpy(temporary, manager.address2);
			}
			else if (addressOption == 3) {
				strcpy(temporary, manager.postCode);
			}
			else {
				strcpy(temporary, manager.state);
			}
			break;
		case 4:
			temp = manager.status;
			break;
		case 5:
			strcpy(temporary, manager.id);
			break;
		case 6:
			temp = manager.gender;
			break;
		case 7:
			strcpy(temporary, manager.age);
			break;
		}


		if ((option == 1 || option == 2 || (option == 3 && addressOption == 1) || option == 5) && strcmp(temporary, input) == 0) {
			printf("---------------------------------------------------\n");
			printf("                Manager Details\n");
			printf("---------------------------------------------------\n");
			printf("ID		: %s\n", manager.id);
			printf("Name		: %s\n", manager.name);
			printf("IC		: %s\n", manager.ic);
			printf("Age		: %s\n", manager.age);
			printf("Gender		: %c\n", manager.gender);
			printf("Status		: %c\n", manager.status);
			printf("Phone Number	: %s\n", manager.phoneNumber);
			printf("Email		: %s\n", manager.email);
			printf("Address	Line 1	: %s\n", manager.address);
			printf("Address	Line 2	: %s\n", manager.address2);
			printf("Postal Code	: %s\n", manager.postCode);
			printf("State		: %s\n", manager.state);
			found = 1;

		}
		else if ((option == 4 || option == 6) && temp == input[0]) {
			if (j == 0) {
				printf("---------------------------------------------------------------------------------\n");
				printf("                                   Manager Details\n");
				printf("---------------------------------------------------------------------------------\n");
				printf("%-7s %-28s %-10s %-7s %s\n", "ID", "Name", "Gender", "Age", "Phone Number\n");
				j++;
			}
			printf("%-7s %-30s %-8c %-8s %s\n", manager.id, manager.name, manager.gender, manager.age, manager.phoneNumber);
			found = 1;
		}
		else if (strcmp(temporary, input) == 0) {
			if (j == 0) {
				printf("---------------------------------------------------------------------------------\n");
				printf("                                   Manager Details\n");
				printf("---------------------------------------------------------------------------------\n");
				printf("%-7s %-28s %-10s %-7s %s\n", "ID", "Name", "Gender", "Age", "Phone Number\n");
				j++;
			}
			printf("%-7s %-30s %-8c %-8s %s\n", manager.id, manager.name, manager.gender, manager.age, manager.phoneNumber);
			found = 1;
		}
	}
	printf("\n\n");

	if (!found && temporary[0] != 'M') {
		printf("No record found for managers\n\n\n");
	}
}

void searchStaff(FILE* staffPtr, char* input, int option, int addressOption) {
	staffDetails staff;
	int found = 0;
	int j = 0; //to display staff title one time
	char temporary[100] = "";
	char temp = ' ';

	while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
		switch (option) {
		case 1:
			strcpy(temporary, staff.name);
			break;
		case 2:
			strcpy(temporary, staff.phoneNumber);
			break;
		case 3:
			if (addressOption == 1) {
				strcpy(temporary, staff.address);
			}
			else if (addressOption == 2) {
				strcpy(temporary, staff.address2);
			}
			else if (addressOption == 3) {
				strcpy(temporary, staff.postCode);
			}
			else {
				strcpy(temporary, staff.state);
			}
			break;
		case 4:
			temp = staff.status;
			break;
		case 5:
			strcpy(temporary, staff.id);
			break;
		case 6:
			temp = staff.gender;
			break;
		case 7:
			strcpy(temporary, staff.age);
			break;
		}


		if ((option == 1 || option == 2 || (option == 3 && addressOption == 1) || option == 5) && strcmp(temporary, input) == 0) {
			if (strcmp(staff.name, "DEL") == 0) {
				printf("\nThis ID is not exist\n");
				system("pause");
				sModuleSearch();
			}
			printf("---------------------------------------------------\n");
			printf("                Staff Details\n");
			printf("---------------------------------------------------\n");
			printf("ID		: %s\n", staff.id);
			printf("Name		: %s\n", staff.name);
			printf("IC		: %s\n", staff.ic);
			printf("Age		: %s\n", staff.age);
			printf("Gender		: %c\n", staff.gender);
			printf("Status		: %c\n", staff.status);
			printf("Phone Number	: %s\n", staff.phoneNumber);
			printf("Email		: %s\n", staff.email);
			printf("Address	Line 1	: %s\n", staff.address);
			printf("Address	Line 2	: %s\n", staff.address2);
			printf("Postal Code	: %s\n", staff.postCode);
			printf("State		: %s\n", staff.state);
			printf("Salary		: RM%.2f\n", staff.salary);
			found = 1;

		}
		else if ((option == 4 || option == 6) && temp == input[0]) {
			if (j == 0) {
				printf("---------------------------------------------------------------------------------\n");
				printf("                                   Staff Details\n");
				printf("---------------------------------------------------------------------------------\n");
				printf("%-7s %-28s %-10s %-7s %s\n", "ID", "Name", "Gender", "Age", "Phone Number\n");
				j++;
			}
			printf("%-7s %-30s %-8c %-8s %s\n", staff.id, staff.name, staff.gender, staff.age, staff.phoneNumber);
			found = 1;
		}
		else if (strcmp(temporary, input) == 0) {
			if (j == 0) {
				printf("---------------------------------------------------------------------------------\n");
				printf("                                   Staff Details\n");
				printf("---------------------------------------------------------------------------------\n");
				printf("%-7s %-28s %-10s %-7s %s\n", "ID", "Name", "Gender", "Age", "Phone Number\n");
				j++;
			}
			printf("%-7s %-30s %-8c %-8s %s\n", staff.id, staff.name, staff.gender, staff.age, staff.phoneNumber);
			found = 1;
		}
	}
	printf("\n\n");

	if (!found && temporary[0] != 'S') {
		printf("No record found for staff\n\n\n");
	}
}

void sModuleSearch() {
	system("cls");
	FILE* managerPtr, * staffPtr;
	managerPtr = fopen("managerFile.bin", "rb");
	staffPtr = fopen("staffFile.bin", "rb");
	if (managerPtr == NULL || staffPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	staffDetails staff;

	int option;
	char input[100];
	char temp;
	double salary;
	int found = 0;
	int j = 0; //to display manager and staff title one time
	int addressOption = 0;


	do {
		system("cls");
		printf("What would you like to search for today?\n");
		printf("--------------------------------------------\n");
		printf("1. Name\n");
		printf("2. Phone Number\n");
		printf("3. Address\n");
		printf("4. Status\n");
		printf("5. ID\n");
		printf("6. Gender\n");
		printf("7. Age\n");
		printf("8. Salary\n");
		printf("9. Exit\n");
		printf("--------------------------------------------\n");
		printf("Select your option (1-9) : ");
		rewind(stdin);
		scanf("%d", &option);
		printf("\n");
	} while (option < 1 || option >9);

	system("cls");
	switch (option) {
	case 1:
		printf("Enter the name : ");
		rewind(stdin);
		scanf(" %[^\n]", input);
		printf("\n\n");
		searchManager(managerPtr, input, option, addressOption);
		searchStaff(staffPtr, input, option, addressOption);
		break;
	case 2:
		printf("Enter the phone number : ");
		rewind(stdin);
		scanf("%s", &input);
		printf("\n\n");
		searchManager(managerPtr, input, option, addressOption);
		searchStaff(staffPtr, input, option, addressOption);
		break;
	case 3:
		do {
			system("cls");
			printf("Address\n");
			printf("--------------------------------------------\n");
			printf("1. Address Line 1\n");
			printf("2. Address Line 2\n");
			printf("3. Postcode\n");
			printf("4. State\n");
			printf("5. Back\n");
			printf("--------------------------------------------\n");
			printf("Select your option (1-5) : ");
			rewind(stdin);
			scanf("%d", &addressOption);
			printf("\n");
		} while (addressOption < 1 || addressOption > 5);

		system("cls");
		if (addressOption == 1) {
			printf("Enter Address Line 1 : ");
			rewind(stdin);
			scanf(" %[^\n]", &input);
			printf("\n\n");
			searchManager(managerPtr, input, option, addressOption);
			searchStaff(staffPtr, input, option, addressOption);
		}

		else if (addressOption == 2) {
			printf("Enter Address Line 2 : ");
			rewind(stdin);
			scanf(" %[^\n]", &input);
			printf("\n\n");
			searchManager(managerPtr, input, option, addressOption);
			searchStaff(staffPtr, input, option, addressOption);
		}

		else if (addressOption == 3) {
			printf("Enter Post Code : ");
			rewind(stdin);
			scanf("%s", &input);
			printf("\n\n");
			searchManager(managerPtr, input, option, addressOption);
			searchStaff(staffPtr, input, option, addressOption);
		}

		else if (addressOption == 4) {
			printf("Enter the state : ");
			rewind(stdin);
			scanf(" %[^\n]", &input);
			printf("\n\n");
			searchManager(managerPtr, input, option, addressOption);
			searchStaff(staffPtr, input, option, addressOption);
		}
		else {
			sModuleSearch();
		}
		break;
	case 4:
		do {
			system("cls");
			printf("Enter the status (F(Full-time) or P(Part-time)): ");
			rewind(stdin);
			scanf(" %c", &temp);
			temp = toupper(temp);
			if (temp != 'P' && temp != 'F') {
				printf("\nInavlid status\nF(Full-time) or P(Part-time)\n");
				system("pause");
			}
			printf("\n\n");
		} while (temp != 'P' && temp != 'F');
		searchManager(managerPtr, &temp, option, addressOption);
		searchStaff(staffPtr, &temp, option, addressOption);
		break;
	case 5:
		printf("Enter the ID: ");
		rewind(stdin);
		scanf(" %[^\n]", &input);
		input[0] = toupper(input[0]);
		printf("\n");
		searchManager(managerPtr, input, option, addressOption);
		searchStaff(staffPtr, input, option, addressOption);
		break;
	case 6:
		do {
			system("cls");
			printf("Enter the gender: ");
			rewind(stdin);
			scanf(" %c", &temp);
			temp = toupper(temp);
			if (temp != 'M' && temp != 'F') {
				printf("\nInavlid gender\nM(Male) or F(Female)\n");
				system("pause");
			}
			printf("\n\n");
		} while (temp != 'M' && temp != 'F');
		searchManager(managerPtr, &temp, option, addressOption);
		searchStaff(staffPtr, &temp, option, addressOption);
		break;
	case 7:
		printf("Enter the age: ");
		rewind(stdin);
		scanf("%s", &input);
		printf("\n\n");
		searchManager(managerPtr, input, option, addressOption);
		searchStaff(staffPtr, input, option, addressOption);
		break;
	case 8:
		printf("Enter the salary : RM");
		rewind(stdin);
		scanf("%lf", &salary);
		printf("\n\n");
		while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
			if (staff.salary == salary) {
				if (j == 0) {
					printf("-----------------------------------------------------------------------------------------\n");
					printf("                                  Staff Details\n");
					printf("-----------------------------------------------------------------------------------------\n");
					printf("%-12s %-7s %-30s %-5s %s\n", "Salary", "ID", "Name", "Age", "Phone Number\n");
					j++;
				}
				printf("RM%-10.2f %-7s %-30s %-6s %s\n", staff.salary, staff.id, staff.name, staff.age, staff.phoneNumber);
				found = 1;
			}
		}
		if (!found) {
			printf("No records found matching the given salary.\n");
		}
		break;
	case 9:
		selectFunction();
		break;
	}

	fclose(managerPtr);
	fclose(staffPtr);

	printf("\n\n");
	system("pause");
	sModuleSearch();
}

void attendance() {
	system("cls");
	FILE* staffPtr;

	staffDetails* staff = malloc(S_MAX_SIZE * sizeof(staffDetails));
	if (staff == NULL) {
		printf("Memory allocation failed\n");
		return;
	}

	char id[6];
	int i = 0;
	int recordS = 0;
	int found = 0;
	int late = 0;
	int answer; //write late reason
	int submit;
	int self = 0;
	int agree;
	int option;
	int edit;
	double totalAttendanceRate = 0, totalLateRate = 0, totalAbsentRate = 0;
	double avgAttendanceRate = 0, avgLateRate = 0, avgAbsentRate = 0;

	time_t t = time(NULL);
	struct tm date = *localtime(&t);
	strcpy(id, logInID);

	if (id[0] == 'S') {

		staffPtr = fopen("staffFile.bin", "rb");
		if (staffPtr == NULL) {
			printf("Unable to open the file\n");
			return;
		}

		int currentDay = date.tm_mday;

		while (fread(&staff[i], sizeof(staffDetails), 1, staffPtr) != 0) {
			if (staff[i].attendanceRate == 0) {
				staff[i].absent = currentDay;
				staff[i].absentRate = 100.00;
			}

			if (strcmp(staff[i].id, id) == 0) {
				self = i;
			}
			i++;
		}
		recordS = i;
		fclose(staffPtr);

		do {
			system("cls");
			printf("Attendance Function\n");
			printf("-------------------------------------------------------------------\n");
			printf("1. Take Attendance\n2. Attendance Rate\n3. Exit\n");
			printf("-------------------------------------------------------------------\n");
			printf("Select your option (1-3) : ");
			scanf("%d", &option);
		} while (option < 1 || option > 3);


		system("cls");
		switch (option) {
		case 1:
			if (date.tm_hour >= 7 && date.tm_hour <= 8) {
				if (staff[self].totalDaysAttend == date.tm_mday) { //prevent get attendance more time in one day
					printf("You already marked attendance today\n\n");
				}
				else {
					// reset attendance rate in new month
					if (staff[self].totalDaysAttend > date.tm_mday) {
						staff[i].attend = 0;
						staff[i].late = 0;
						staff[i].absent = 0;
						memset(staff[i].lateReason, 0, sizeof(staff[i].lateReason));
						strcpy(staff[i].lateReason, "no");
						staff[i].totalDaysAttend = 0;
					}
					staff[self].attend += 1;
					staff[self].totalDaysAttend = date.tm_mday;
					printf("Successful register in %d-%02d-%02d %02d:%02d\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min);
					printf("Have a good day\n");
				}

			}
			else if (date.tm_hour < 7) {
				printf("You are too early\n");
				printf("Please sign in attedance after 7.00 a.m.\n");
			}
			else if (date.tm_hour >= 1 && date.tm_hour < 17) {
				if (staff[self].totalDaysAttend == date.tm_mday) { //prevent get attendance more time in one day
					printf("You already marked attendance today\n\n");
				}
				else {
					// reset attendance rate in new month
					if (staff[self].totalDaysAttend > date.tm_mday) {
						staff[i].attend = 0;
						staff[i].late = 0;
						staff[i].absent = 0;
						memset(staff[i].lateReason, 0, sizeof(staff[i].lateReason));
						strcpy(staff[i].lateReason, "no");
						staff[i].totalDaysAttend = 0;
					}
					do {
						system("cls");
						printf("Too late!!!\n");
						printf("You cannot get attendance today\n\n");
						printf("\nWould you like to write a reason for your late attendance to receive credit?\n");
						printf("----------------------------------------------------------------------------------\n");
						printf("1. Yes\n2. N0\n");
						printf("----------------------------------------------------------------------------------\n");
						printf("Select your option (1-2) : ");
						rewind(stdin);
						scanf("%d", &answer);
						printf("\n");
					} while (answer < 1 || answer > 2);

					if (answer == 1) {
						do {
							system("cls");
							printf("Write down your reason :\n");
							rewind(stdin);
							scanf(" %[^\n]", staff[self].lateReason);
							do {
								printf("\n\n\nSubmit ?\n--------------------------------------\n1. Yes\n2. Write again\n--------------------------------------\nSelect your option (1-2) : ");
								rewind(stdin);
								scanf("%d", &submit);
							} while (submit < 1 || submit > 2);
						} while (submit == 2);
						printf("\n\n\nProcess Successful\n");
					}

					staff[self].late += 1;
					staff[self].totalDaysAttend = date.tm_mday;
				}
			}
			else if (date.tm_hour >= 17) {
				printf("Already off\n");
			}


			if (staff[self].totalDaysAttend > 0) {
				staff[self].attendanceRate = ((double)staff[self].attend / staff[self].totalDaysAttend) * 100;
				staff[self].lateRate = ((double)staff[self].late / staff[self].totalDaysAttend) * 100;
				staff[self].absent = staff[self].totalDaysAttend - staff[self].attend;
				staff[self].absentRate = ((double)staff[self].absent / staff[self].totalDaysAttend) * 100;
			}


			staffPtr = fopen("staffFile.bin", "wb");
			if (staffPtr == NULL) {
				printf("Unable to open the file\n");
				return;
			}

			for (int self = 0; self < recordS; self++) {
				fwrite(&staff[self], sizeof(staffDetails), 1, staffPtr);
			}

			fclose(staffPtr);
			break;
		case 2:
			system("cls");
			printf("ID		: %s\n", staff[self].id);
			printf("Attendance Rate	: %.2f%%\n", staff[self].attendanceRate);
			printf("Late Rate	: %.2f%%\n", staff[self].lateRate);
			printf("Absent Rate	: %.2f%%\n", staff[self].absentRate);
			break;
		case 3:
			selectFunction();
			break;
		}
	}
	else {
		do {
			system("cls");
			printf("Attendance Function\n");
			printf("-------------------------------------------------------------------\n");
			printf("1. Attendance Report\n");
			printf("2. View Staff Late Reason\n");
			printf("3. Exit\n");
			printf("-------------------------------------------------------------------\n");
			printf("Select your option (1-3) : ");
			rewind(stdin);
			scanf("%d", &option);
			printf("\n");
		} while (option < 1 || option > 3);
		system("cls");

		switch (option) {
		case 1:
			//report
			staffPtr = fopen("staffFile.bin", "rb");
			if (staffPtr == NULL) {
				printf("Unable to open the file\n");
				return;
			}

			i = 0;
			int j = 0;
			int currentDay = date.tm_mday;

			while (fread(&staff[i], sizeof(staffDetails), 1, staffPtr) != 0) {

				if (strcmp(staff[i].name, "DEL") == 0) {
					continue;
				}
				else {
					if (staff[i].attendanceRate == 0) {
						staff[i].absent = currentDay;
						staff[i].absentRate = 100.00;
					}

					// reset attendance rate in new month
					if (staff[i].totalDaysAttend > currentDay) {
						staff[i].attend = 0;
						staff[i].late = 0;
						staff[i].absent = 0;
						staff[i].attendanceRate = 0;
						staff[i].lateRate = 0;
						staff[i].absentRate = 0;
						memset(staff[i].lateReason, 0, sizeof(staff[i].lateReason));
						strcpy(staff[i].lateReason, "no");
						staff[i].totalDaysAttend = 0;
					}

					if (j == 0) {
						printf("------------------------------------------------------------------------------------------------------------------------\n");
						printf("%-7s %-24s %-14s %-12s %-14s %-18s %-12s %s\n", "ID", "Name", "Attend Time", "Late Time", "Absent Time", "Attendance Rate", "Late Rate", "Absent Rate");
						printf("------------------------------------------------------------------------------------------------------------------------\n");
						j++;
					}
					printf("%-7s %-28s %-14d %-13d %-14d %-15.2f %-13.2f %.2f\n", staff[i].id, staff[i].name, staff[i].attend, staff[i].late, staff[i].absent, staff[i].attendanceRate, staff[i].lateRate, staff[i].absentRate);
					totalAttendanceRate += staff[i].attendanceRate;
					totalLateRate += staff[i].lateRate;
					totalAbsentRate += staff[i].absentRate;
				}
				i++;
			}
			avgAttendanceRate = totalAttendanceRate / i;
			avgLateRate = totalLateRate / i;
			avgAbsentRate = totalAbsentRate / i;
			printf("\n\nAverage Attendance Rate : %.2f%%\n", avgAttendanceRate);
			printf("Average Late Rate	: %.2f%%\n", avgLateRate);
			printf("Average Absent Rate	: %.2f%%\n", avgAbsentRate);

			fclose(staffPtr);
			break;

		case 2:
			staffPtr = fopen("staffFile.bin", "rb");
			if (staffPtr == NULL) {
				printf("Unable to open the file\n");
				return;
			}

			i = 0;
			while (fread(&staff[i], sizeof(staffDetails), 1, staffPtr) != 0) {
				i++;
			}
			recordS = i;

			fclose(staffPtr);

			for (int i = 0; i < recordS; i++) {
				if (strcmp(staff[i].lateReason, "no") != 0 && strcmp(staff[i].name, "DEL") != 0) {
					do {
						system("cls");
						printf("%s has submitted a late reason.\n", staff[i].id);
						printf("Would you like to read it?\n");
						printf("--------------------------------------\n");
						printf("1. Yes\n2. No\n");
						printf("--------------------------------------\n");
						printf("Select your option : ");
						rewind(stdin);
						scanf("%d", &answer);
					} while (answer < 1 || answer > 2);

					if (answer == 1) {
						do {
							system("cls");
							printf("%s Late Reason\n", staff[i].id);
							printf("--------------------------------------\n");
							printf("%s\n\n\n\n", staff[i].lateReason);
							printf("Do you agree with this reason?\n");
							printf("--------------------------------------\n");
							printf("1. Yes\n2. No\n");
							printf("--------------------------------------\n");
							printf("Select your option (1-2) : ");
							rewind(stdin);
							scanf("%d", &agree);
						} while (agree < 1 || agree > 2);

						if (agree == 1) {
							do {
								system("cls");
								printf("ID		: %s\nAttendance rate	: %.2f\nLate Rate	: %.2f\nAbsent Rate	: %.2f\n\n\n", staff[i].id, staff[i].attendanceRate, staff[i].lateRate, staff[i].absentRate);
								printf("Do you want to grant attendance credit?\n");
								printf("--------------------------------------------\n");
								printf("1. Yes\n2. No\n");
								printf("--------------------------------------------\n");
								printf("Select your option (1-2) : ");
								rewind(stdin);
								scanf("%d", &edit);
							} while (edit < 1 || edit > 2);

							if (edit == 1) {
								system("cls");
								staff[i].attend++;
								staff[i].absent--;
								memset(staff[i].lateReason, 0, sizeof(staff[i].lateReason));
								strcpy(staff[i].lateReason, "no");
								staff[i].attendanceRate = ((double)staff[i].attend / staff[i].totalDaysAttend) * 100;
								staff[i].lateRate = ((double)staff[i].late / staff[i].totalDaysAttend) * 100;
								staff[i].absentRate = ((double)staff[i].absent / staff[i].totalDaysAttend) * 100;
								printf("ID		: %s\nAttendance rate	: %.2f\nLate Rate	: %.2f\nAbsent Rate	: %.2f\n\n\n", staff[i].id, staff[i].attendanceRate, staff[i].lateRate, staff[i].absentRate);
								printf("Process Successful\n");
								system("pause");
							}
							else {
								memset(staff[i].lateReason, 0, sizeof(staff[i].lateReason));
								strcpy(staff[i].lateReason, "no");
							}
						}
						else {
							memset(staff[i].lateReason, 0, sizeof(staff[i].lateReason));
							strcpy(staff[i].lateReason, "no");
						}
					}
					found = 1;
				}
			}

			if (found) {
				staffPtr = fopen("staffFile.bin", "wb");
				if (staffPtr == NULL) {
					printf("Unable to open the file\n");
					return;
				}
				for (int i = 0; i < recordS; i++) {
					fwrite(&staff[i], sizeof(staffDetails), 1, staffPtr);
				}
				fclose(staffPtr);
			}
			else {
				printf("No Record\n");
			}
			break;

		case 3:
			selectFunction();
			break;
		}
	}
	printf("\n\n");
	free(staff);
	system("pause");
	attendance();
}

void modifyEditTable(int option, char* input, int addressOption) {
	FILE* managerPtr, * staffPtr;
	managerPtr = fopen("managerFile.bin", "rb");
	staffPtr = fopen("staffFile.bin", "rb");
	if (managerPtr == NULL || staffPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	management* manager = (management*)malloc(M_MAX_SIZE * sizeof(management));
	staffDetails* staff = (staffDetails*)malloc(S_MAX_SIZE * sizeof(staffDetails));
	if (manager == NULL || staff == NULL) {
		printf("Memory allocation failed\n");
		return;
	}

	int confirm = -1;
	char temporary[1000];
	char temp;
	int k;
	int checkIC = 0;

	switch (option) {
	case 1:
		do {
			system("cls");
			printf("Edit Information\n");
			printf("Enter New Name : ");
			rewind(stdin);
			scanf(" %[^\n]", temporary);
			if (!isValidName(temporary)) {
				printf("Invalid Name (No Special Character or Number)\n");
				system("pause");
			}
		} while (!isValidName(temporary));

		do {
			system("cls");
			printf("Current Name	: %s\n", input);
			printf("New Name	: %s\n", temporary);
			printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
			rewind(stdin);
			scanf("%d", &confirm);
		} while (confirm < 1 || confirm > 2);

		printf("\n");;
		break;
	case 2:
		do {
			do {
				system("cls");
				printf("Edit Information\n");
				printf("Enter New IC : ");
				scanf("%s", temporary);
				if (!isValidIC(temporary)) {
					printf("Invalid IC : %s\n", temporary);
					system("pause");
				}
			} while (!isValidIC(temporary));

			rewind(managerPtr);
			checkIC = 1; // Assume the IC is unique until proven otherwise
			k = 0; // Reset k to 0 before searching for matching ICs
			while (fread(&manager[k], sizeof(management), 1, managerPtr) != 0) {
				if (strcmp(manager[k].ic, temporary) == 0) {
					printf("%-7s %-20s %s\n\n\n", manager[k].id, manager[k].name, manager[k].ic);
					checkIC = 0;
					break;
				}
				k++;
			}
			rewind(staffPtr);
			k = 0;
			while (fread(&staff[k], sizeof(staffDetails), 1, staffPtr) != 0) {
				if (strcmp(staff[k].ic, temporary) == 0) {
					printf("This IC is already registered\n");
					checkIC = 0;
					break;
				}
				k++;
			}
		} while (!checkIC);

		do {
			system("cls");
			printf("Current IC	: %s\n", input);
			printf("New IC		: %s\n", temporary);
			printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
			rewind(stdin);
			scanf("%d", &confirm);
		} while (confirm < 1 || confirm > 2);

		printf("\n");
		break;
	case 3:
		do {
			system("cls");
			printf("Edit Information\n");
			printf("Enter New Age : ");
			rewind(stdin);
			scanf("%s", temporary);
			if (!isValidAge(temporary)) {
				printf("Not meeting the entry age(18-45)\n");
				system("pause");
			}
		} while (!isValidAge(temporary));

		do {
			system("cls");
			printf("Current Age	: %s\n", input);
			printf("New Age		: %s\n", temporary);
			printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
			rewind(stdin);
			scanf("%d", &confirm);
		} while (confirm < 1 || confirm > 2);

		if (confirm == 1) {
			strcpy(input, temporary);
			printf("\n\nEdit Successful\n");
		}
		break;
	case 4:
		do {
			system("cls");
			printf("Edit Information\n");
			printf("Enter New Gender : ");
			rewind(stdin);
			scanf("%c", &temp);
			temp = toupper(temp);
			if (temp != 'M' && temp != 'F') {
				printf("Invalid Input M(Male) or F(Female)\n");
				system("pause");
			}
		} while (temp != 'M' && temp != 'F');

		do {
			system("cls");
			printf("Current Gender	: %c\n", input[0]);
			printf("New Gender	: %c\n", temp);
			printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
			rewind(stdin);
			scanf("%d", &confirm);
		} while (confirm < 1 || confirm > 2);

		if (confirm == 1) {
			input[0] = temp;
			printf("\n\nEdit Successful\n");
		}

		printf("\n");
		break;
	case 5:
		do {
			system("cls");
			printf("Edit Information\n");
			printf("Enter New Phone Number : ");
			rewind(stdin);
			scanf("%s", &temporary);
			if (!isValidPhone(temporary)) {
				printf("Invalid Phone Number\n");
				system("pause");
			}
		} while (!isValidPhone(temporary));

		do {
			system("cls");
			printf("Current Phone Number	: %s\n", input);
			printf("New Phone Number	: %s\n", temporary);
			printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
			rewind(stdin);
			scanf("%d", &confirm);
		} while (confirm < 1 || confirm > 2);

		printf("\n");
		break;
	case 6:
		do {
			system("cls");
			printf("Edit Information\n");
			printf("Enter New Email : ");
			rewind(stdin);
			scanf("%s", &temporary);
			if (!isValidEmail(temporary)) {
				printf("Invalid Email\n");
				system("pause");
			}
		} while (!isValidEmail(temporary));


		do {
			system("cls");
			printf("Current Email	: %s\n", input);
			printf("New Email	: %s\n", temporary);
			printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
			rewind(stdin);
			scanf("%d", &confirm);
		} while (confirm < 1 || confirm > 2);

		printf("\n");
		break;
	case 7:

		if (addressOption == 1) {
			do {
				system("cls");
				printf("Edit Address\n---------------------------------\n");
				printf("Enter New Address Line 1 : ");
				rewind(stdin);
				scanf(" %[^\n]", &temporary);
				if (!isValidAddress(temporary)) {
					printf("Invalid Address Line 1\n");
					system("pause");
				}
			} while (!isValidAddress(temporary));

			do {
				system("cls");
				printf("Current Address Line 1	: %s\n", input);
				printf("New Address Line 1	: %s\n", temporary);
				printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
				scanf("%d", &confirm);
			} while (confirm < 1 || confirm > 2);

			printf("\n");
		}
		else if (addressOption == 2) {
			do {
				system("cls");
				printf("Edit Address\n---------------------------------\n");
				printf("Enter New Address Line 2 : ");
				rewind(stdin);
				scanf(" %[^\n]", &temporary);
				if (!isValidAddress2(temporary)) {
					printf("Invalid Address Line 2\n");
					system("pause");
				}
			} while (!isValidAddress2(temporary));

			do {
				system("cls");
				printf("Current Address Line 2	: %s\n", input);
				printf("New Address Line 2	: %s\n", temporary);
				printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
				scanf("%d", &confirm);
			} while (confirm < 1 || confirm > 2);

			printf("\n");
		}
		else if (addressOption == 3) {
			do {
				system("cls");
				printf("Edit Address\n---------------------------------\n");
				printf("Enter New PostCode : ");
				rewind(stdin);
				scanf("%s", &temporary);
				if (!isValidPostCode(temporary)) {
					printf("Invalid Post Code\n");
					system("pause");
				}
			} while (!isValidPostCode(temporary));

			do {
				system("cls");
				printf("Current PostCode	: %s\n", input);
				printf("New PostCode		: %s\n", temporary);
				printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
				scanf("%d", &confirm);
			} while (confirm < 1 || confirm > 2);

			printf("\n");
		}
		else {
			do {
				system("cls");
				printf("Edit Address\n---------------------------------\n");
				printf("Enter New State : ");
				rewind(stdin);
				scanf(" %[^\n]", &temporary);
				if (!isValidState(temporary)) {
					printf("Invalid State");
					system("pause");
				}
			} while (!isValidState(temporary));

			do {
				system("cls");
				printf("Current State	: %s\n", input);
				printf("New State	: %s\n", temporary);
				printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
				scanf("%d", &confirm);
			} while (confirm < 1 || confirm > 2);

			printf("\n");
		}
		break;
	case 8:
		do {
			system("cls");
			printf("Change Password\n");
			printf("-----------------------------------------\n");
			printf("Enter New Password : ");
			rewind(stdin);
			scanf(" %[^\n]", &temporary);
			if (!isValidPassword(temporary)) {
				printf("Password is invalid.\n");
				printf("Note : \n");
				printf("1. No contain space\n");
				system("pause");
			}
		} while (!isValidPassword(temporary));

		do {
			system("cls");
			printf("Current Password	: %s\n", input);
			printf("New Password		: %s\n", temporary);
			printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
			rewind(stdin);
			scanf("%d", &confirm);
		} while (confirm < 1 || confirm > 2);
		break;
	case 9:
		system("cls");

		static int j = 0;
		system("cls");
		printf("Change Password Recovery Answer\n");
		printf("----------------------------------------------------------------\n");
		printf("Question %d	: %s ?\n", j + 1, recovery[j].question);
		printf("New Answer	: ");
		rewind(stdin);
		scanf(" %[^\n]", temporary);

		do {
			system("cls");
			printf("Question %d Current Answer	: %s\n", j + 1, input);
			printf("Question %d New Answer		: %s\n", j + 1, temporary);
			printf("\n\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
			rewind(stdin);
			scanf("%d", &confirm);
			printf("\n\n");
			system("pause");
		} while (confirm < 1 || confirm > 2);

		if (confirm == 1) {
			memset(input, 0, sizeof(input));
			strcpy(input, temporary);
			printf("\n\nProcess Successful\n");
		}

		if (j < 5) {
			j++;
		}
		break;
	}

	if (confirm == 1 && option != 3 && option != 4 && option != 9) {
		memset(input, 0, sizeof(input));
		strcpy(input, temporary);
		printf("\nEdit Successful\n");
	}
	fclose(staffPtr);
	fclose(managerPtr);
	free(manager);
	free(staff);
}

void sModuleModify() {
	FILE* managerPtr, * staffPtr;
	managerPtr = fopen("managerFile.bin", "rb");
	staffPtr = fopen("staffFile.bin", "rb");
	if (managerPtr == NULL || staffPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	management* manager = (management*)malloc(M_MAX_SIZE * sizeof(management));
	staffDetails* staff = (staffDetails*)malloc(S_MAX_SIZE * sizeof(staffDetails));
	if (manager == NULL || staff == NULL) {
		printf("Memory allocation failed\n");
		return;
	}

	int option, addressOption = 0;
	int people; //decide modify self data or staff
	int m = 0;
	int s = 0; // to find staff in array
	int recordM = 0; //find how many set of manager data in file
	int recordS = 0; //find how many set of staff data in file
	int self = 0; // to edit self data
	char staffID[6]; //manager modify staff information
	int confirm;
	int passwordOption; //decide need enter again or exit (in case 8 modify password side)
	char verifyPassword[13];
	char id[5];
	char status;
	double salary;
	int found = 0;

	strcpy(id, logInID);

	recordM = 0;
	while (fread(&manager[recordM], sizeof(management), 1, managerPtr) != 0) {
		if (strcmp(manager[recordM].id, id) == 0) {
			found++;
			self = recordM;
		}
		recordM++;
	}

	recordS = 0;
	while (fread(&staff[recordS], sizeof(staffDetails), 1, staffPtr) != 0) {
		if (strcmp(staff[recordS].id, id) == 0) {
			found++;
			self = recordS;
		}
		recordS++;
	}

	fclose(managerPtr);
	fclose(staffPtr);


	if (id[0] == 'M') {
		do {
			system("cls");
			printf("Edit Table\n");
			printf("---------------------------------\n");
			printf("1. Me\n");
			printf("2. Staff\n");
			printf("3. Exit\n");
			printf("---------------------------------\n");
			printf("Select your option (1-3) : ");
			rewind(stdin);
			scanf("%d", &people);
			if (people < 1 || people>3) {
				printf("Invalid Option\n\n");
			}
		} while (people < 1 || people>3);

		switch (people) {
		case 1:
			// select what need to modify
			do {
				system("cls");
				printf("Edit Table\n");
				printf("---------------------------------\n");
				printf("1. Name\n");
				printf("2. IC Numbers\n");
				printf("3. Age\n");
				printf("4. Gender\n");
				printf("5. Phone Number\n");
				printf("6. Email\n");
				printf("7. Address\n");
				printf("8. Password\n");
				printf("9. Password Recovery Answer\n");
				printf("10. Back\n");
				printf("---------------------------------\n");
				printf("Select you option (1-9) : ");
				rewind(stdin);
				scanf("%d", &option);
				if (option < 1 || option > 10) {
					printf("Invalid Option\n\n");
				}
			} while (option < 1 || option > 10);

			switch (option) {
			case 1:
				modifyEditTable(option, &manager[self].name, addressOption);
				break;

			case 2:
				modifyEditTable(option, &manager[self].ic, addressOption);
				break;

			case 3:
				modifyEditTable(option, &manager[self].age, addressOption);
				break;

			case 4:
				modifyEditTable(option, &manager[self].gender, addressOption);
				break;

			case 5:
				modifyEditTable(option, &manager[self].phoneNumber, addressOption);
				break;

			case 6:
				modifyEditTable(option, &manager[self].email, addressOption);
				break;

			case 7:
				do {
					system("cls");
					printf("Which part you want to edit\n");
					printf("-----------------------------------------\n");
					printf("1. Address Line 1\n");
					printf("2. Address Line 2\n");
					printf("3. PostCode\n");
					printf("4. State\n");
					printf("-----------------------------------------\n");
					printf("Select your option (1-4) : ");
					rewind(stdin);
					scanf("%d", &addressOption);
				} while (addressOption < 1 || addressOption>4);

				if (addressOption == 1) {
					modifyEditTable(option, &manager[self].address, addressOption);
				}
				else if (addressOption == 2) {
					modifyEditTable(option, &manager[self].address2, addressOption);
				}
				else if (addressOption == 3) {
					modifyEditTable(option, &manager[self].postCode, addressOption);
				}
				else {
					modifyEditTable(option, &manager[self].state, addressOption);
				}
				break;

			case 8:
				do {
					system("cls");
					printf("Change Password\n");
					printf("-----------------------------------------\n");
					printf("Enter current password : ");
					rewind(stdin);
					scanf(" %[^\n]", &verifyPassword);
					printf("\n");

					if (strcmp(manager[self].password, verifyPassword) != 0)
					{
						do {
							printf("\n\nWrong Password\n");
							printf("1. Enter again\n");
							printf("2. Exit\n");
							printf("Select your option : ");
							rewind(stdin);
							scanf("%d", &passwordOption);
						} while (passwordOption < 1 || passwordOption > 2);
					}
					else {
						passwordOption = 2;
					}
				} while (passwordOption == 1);

				if (strcmp(manager[self].password, verifyPassword) == 0) {
					modifyEditTable(option, &manager[self].password, addressOption);
				}
				break;

			case 9:
				do {
					system("cls");
					printf("Change Password Recovery Answer\n");
					printf("-----------------------------------------\n");
					printf("Enter your password : ");
					rewind(stdin);
					scanf(" %[^\n]", &verifyPassword);
					printf("\n");

					if (strcmp(manager[self].password, verifyPassword) != 0)
					{
						do {
							printf("\n\nWrong Password\n");
							printf("1. Enter again\n");
							printf("2. Exit\n");
							printf("Select your option : ");
							rewind(stdin);
							scanf("%d", &passwordOption);
						} while (passwordOption < 1 || passwordOption > 2);
					}
					else {
						passwordOption = 2;
					}
				} while (passwordOption == 1);


				if (strcmp(manager[self].password, verifyPassword) == 0) {
					for (int j = 0; j < 5; j++) {
						modifyEditTable(option, &manager[self].recovery[j].answer, addressOption);
					}
				}
				break;

			case 10:
				sModuleModify();
				break;
			}
			break;

		case 2:
			do {
				system("cls");
				printf("Edit Table\n");
				printf("-----------------------------------------\n");
				printf("1. Status\n");
				printf("2. Salary\n");
				printf("3. Back\n");
				printf("-----------------------------------------\n");
				printf("Select you want edit : ");
				rewind(stdin);
				scanf("%d", &option);
			} while (option < 1 || option > 3);

			system("cls");
			printf("Enter Staff's ID : ");
			rewind(stdin);
			scanf("%s", &staffID);
			staffID[0] = toupper(staffID[0]);
			staffPtr = fopen("staffFile.bin", "rb");
			recordS = 0;
			s = 0;
			int cont = 0;
			found = 0;

			while (fread(&staff[s], sizeof(staffDetails), 1, staffPtr) != 0) {
				if (strcmp(staff[s].id, staffID) == 0) {
					found++;
					cont = s;
				}
				s++;
			}
			recordS = s;

			fclose(staffPtr);

			if (strcmp(staff[cont].name, "DEL") == 0) {
				printf("\nThis ID is not exist\n");
				break;
			}
			// select what need to modify

			if (found) {

				switch (option) {
				case 1:
					do {
						do {
							printf("\n\nCurrent Status	 : %c\n", staff[cont].status);
							printf("Update Status	 : ");
							rewind(stdin);
							scanf("%c", &status);
							status = toupper(status);
							if (status != 'P' && status != 'F') {
								printf("Invalid Input F(Full-Time) or P(Part-Time)\n");
								system("pause");
							}
						} while (status != 'F' && status != 'P');


						do {
							printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
							rewind(stdin);
							scanf("%d", &confirm);
						} while (confirm < 1 || confirm > 2);

						if (confirm == 1) {
							staff[cont].status = status;
							printf("\n\nUpdate Successful\n");
						}
					} while (confirm != 1);
					printf("\n");
					break;
				case 2:
					do {
						printf("\n\nCurrent Salary	 : RM%.2f\n", staff[cont].salary);
						printf("Update Salary	 : RM");
						rewind(stdin);
						scanf("%lf", &salary);
						do {
							printf("\n\nConfirm Edit ?\n---------------------------------\n1. Yes\n2. No\n---------------------------------\nSelect your option (1-2) : ");
							rewind(stdin);
							scanf("%d", &confirm);
						} while (confirm < 1 || confirm > 2);

						if (confirm == 1) {
							staff[cont].salary = salary;
						}
						else {
							salary = 0.00;
						}
					} while (confirm != 1);
					printf("\n");
					break;
				case 3:
					sModuleModify();
					break;
				}
			}
			break;

		case 3:
			selectFunction();
			break;
		}
	}

	else {
		// select what need to modify
		do {
			system("cls");
			printf("Edit Table\n");
			printf("-----------------------------------------\n");
			printf("1. Name\n");
			printf("2. IC Numbers\n");
			printf("3. Age\n");
			printf("4. Gender\n");
			printf("5. Phone Number\n");
			printf("6. Email\n");
			printf("7. Address\n");
			printf("8. Password\n");
			printf("9. Password Recovery Answer\n");
			printf("10. Back\n");
			printf("-----------------------------------------\n");
			printf("Select you option : ");
			rewind(stdin);
			scanf("%d", &option);
			printf("\n");
			if (option < 1 || option > 10) {
				printf("Invalid Option\n\n");
			}
		} while (option < 1 || option > 10);
		printf("\n");

		switch (option) {
		case 1:
			modifyEditTable(option, &staff[self].name, addressOption);
			break;

		case 2:
			modifyEditTable(option, &staff[self].ic, addressOption);
			break;

		case 3:
			modifyEditTable(option, &staff[self].age, addressOption);
			break;

		case 4:
			modifyEditTable(option, &staff[self].gender, addressOption);
			break;

		case 5:
			modifyEditTable(option, &staff[self].phoneNumber, addressOption);
			break;

		case 6:
			modifyEditTable(option, &staff[self].email, addressOption);
			break;

		case 7:
			do {
				system("cls");
				printf("Which part you want to edit\n");
				printf("-----------------------------------------\n");
				printf("1. Address Line 1\n");
				printf("2. Address Line 2\n");
				printf("3. PostCode\n");
				printf("4. State\n");
				printf("5. Back\n");
				printf("-----------------------------------------\n");
				printf("Select your option (1-5) : ");
				rewind(stdin);
				scanf("%d", &addressOption);
			} while (addressOption < 1 || addressOption>5);

			if (addressOption == 1) {
				modifyEditTable(option, &staff[self].address, addressOption);
			}
			else if (addressOption == 2) {
				modifyEditTable(option, &staff[self].address2, addressOption);
			}
			else if (addressOption == 3) {
				modifyEditTable(option, &staff[self].postCode, addressOption);
			}
			else if (addressOption == 4) {
				modifyEditTable(option, &staff[self].state, addressOption);
			}
			else {
				sModuleModify();
			}
			break;

		case 8:
			do {
				system("cls");
				printf("Change Password\n");
				printf("-----------------------------------------\n");
				printf("Enter current password : ");
				rewind(stdin);
				scanf(" %[^\n]", &verifyPassword);
				printf("\n");

				if (strcmp(staff[self].password, verifyPassword) != 0)
				{
					do {
						printf("\n\nWrong Password\n");
						printf("1. Enter again\n");
						printf("2. Exit\n");
						printf("Select your option : ");
						rewind(stdin);
						scanf("%d", &passwordOption);
					} while (passwordOption < 1 || passwordOption > 2);
				}
				else {
					passwordOption = 2;
				}
			} while (passwordOption == 1);

			if (strcmp(staff[self].password, verifyPassword) == 0) {
				modifyEditTable(option, &staff[self].password, addressOption);
			}
			break;

		case 9:
			do {
				system("cls");
				printf("Change Password Recovery Answer\n");
				printf("-----------------------------------------\n");
				printf("Enter your password : ");
				rewind(stdin);
				scanf(" %[^\n]", &verifyPassword);
				printf("\n");

				if (strcmp(staff[self].password, verifyPassword) != 0)
				{
					do {
						printf("\n\nWrong Password\n");
						printf("1. Enter again\n");
						printf("2. Exit\n");
						printf("Select your option : ");
						rewind(stdin);
						scanf("%d", &passwordOption);
					} while (passwordOption < 1 || passwordOption > 2);
				}
				else {
					passwordOption = 2;
				}
			} while (passwordOption == 1);

			if (strcmp(staff[self].password, verifyPassword) == 0) {
				for (int j = 0; j < 5; j++) {
					modifyEditTable(option, &staff[self].recovery[j].answer, addressOption);
				}
				printf("\nProcess Successful\n");
			}
			break;

		case 10:
			selectFunction();
			break;
		}
	}

	if (found) {
		managerPtr = fopen("managerFile.bin", "wb");
		staffPtr = fopen("staffFile.bin", "wb");
		if (managerPtr == NULL || staffPtr == NULL) {
			printf("Unable to open the file\n");
			return;
		}


		for (int m = 0; m < recordM; m++) {
			fwrite(&manager[m], sizeof(management), 1, managerPtr);
		}

		for (int s = 0; s < recordS; s++) {
			fwrite(&staff[s], sizeof(staffDetails), 1, staffPtr);
		}


		fclose(managerPtr);
		fclose(staffPtr);
	}
	else {
		printf("\nThis ID havent signup\n");
	}

	free(manager);
	free(staff);
	system("pause");
	sModuleModify();
}

void sModuleAdd() {
	FILE* staffPtr, * managerPtr;
	staffPtr = fopen("staffFile.bin", "rb");
	managerPtr = fopen("managerFile.bin", "rb");
	if (staffPtr == NULL || managerPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	staffDetails* staff = malloc(S_MAX_SIZE * sizeof(staffDetails));
	if (staff == NULL) {
		printf("Memory allocation failed\n");
		return;
	}

	staffDetails temporaryS;
	management manager;

	char staffID[5] = "S001";
	int i = 0, option;
	int recordS = 0;
	int self = 0;
	int temporarySelf = -1;
	char temporaryID[5];
	int k = 0;
	int checkIC = 0;
	int count = 0;

	do {
		system("cls");
		printf("Add Function\n");
		printf("-------------------------------------------\n");
		printf("1. Add New Staff Account\n");
		printf("2. Exit\n");
		printf("-------------------------------------------\n");
		printf("Select your option (1-2) : ");
		rewind(stdin);
		scanf("%d", &option);
		printf("\n");
	} while (option < 1 || option > 2);

	system("cls");
	switch (option) {
	case 1:
		for (int i = 0; i < S_MAX_SIZE; i++) {
			if (fread(&staff[i], sizeof(staffDetails), 1, staffPtr) != 0) {
				if (strcmp(staff[i].id, staffID) == 0 && strcmp(staff[i].name, "DEL") == 0) {
					self = i;
					temporarySelf = self;
					strcpy(temporaryID, staffID);
					count++;
					if (staffID[3] == '9') {
						staffID[3] = '0';
						staffID[2]++;
					}
					else {
						staffID[3]++;
					}
				}
				else if (strcmp(staff[i].id, staffID) == 0) {
					if (staffID[3] == '9') {
						staffID[3] = '0';
						staffID[2]++;
					}
					else {
						staffID[3]++;
					}
					recordS++;
					count++;
				}
				else {
					self = i;
					recordS++;
					break;
				}
			}
			else {
				self = i;
				recordS++;
				break;
			}
		}

		if (count >= S_MAX_SIZE) {
			printf("Maximum number of staff accounts (%d) has already been reached.\n", S_MAX_SIZE);
		}

		if (temporarySelf >= 0) {
			self = temporarySelf;
		}

		do {
			system("cls");
			printf("Enter New Staff Information\n");
			printf("-------------------------------------------\n");
			printf("Name (X to Exit): ");
			rewind(stdin);
			scanf(" %[^\n]", staff[self].name);
			if (strcmp(staff[self].name, "X") == 0 || strcmp(staff[self].name, "x") == 0) {
				sModuleMain();
			}
			if (!isValidName(staff[self].name)) {
				printf("Invalid Name (No Special Character or Number)\n");
				system("pause");
			}
		} while (!isValidName(staff[self].name));


		do {
			printf("IC		: ");
			scanf("%s", staff[self].ic);
			while (!isValidIC(staff[self].ic)) {
				printf("\nInvalid IC\n");
				printf("1. IC must have 12 characters\n2. Ensure first 6 character is valid year, month and day\n\n");
				printf("IC		: ");
				rewind(stdin);
				scanf("%s", staff[self].ic);
			}

			rewind(staffPtr);
			checkIC = 1; // Assume the IC is unique until proven otherwise
			while (fread(&temporaryS, sizeof(staffDetails), 1, staffPtr) != 0) {
				if (strcmp(temporaryS.ic, staff[self].ic) == 0) {
					if (self == k) {
						continue;
					}
					printf("This IC is already registered\n");
					checkIC = 0;
					break;
				}
			}

			rewind(managerPtr);
			while (fread(&manager, sizeof(management), 1, managerPtr) != 0) {
				if (strcmp(manager.ic, staff[self].ic) == 0) {
					printf("This IC is already registered\n");
					checkIC = 0;
					break;
				}
			}
		} while (!checkIC);

		fclose(staffPtr);
		fclose(managerPtr);

		do {
			printf("Age		: ");
			rewind(stdin);
			scanf("%s", &staff[self].age);
			if (!isValidAge(staff[self].age)) {
				printf("Not meeting the entry age (18-45)\n");
			}
		} while (!isValidAge(staff[self].age));


		if (staff[self].ic[11] % 2 != 0) {
			staff[self].gender = 'M'; // Odd digit indicates male
		}
		else if (staff[self].ic[11] % 2 == 0) {
			staff[self].gender = 'F'; // Even digit indicates female
		}


		do {
			printf("Status (F/P)	: ");
			rewind(stdin);
			scanf("%c", &staff[self].status);
			staff[self].status = toupper(staff[self].status);
			if (staff[self].status != 'F' && staff[self].status != 'P') {
				printf("Invalid Option F(Full-time) or P(Part-time)\n");
			}
		} while (staff[self].status != 'F' && staff[self].status != 'P');


		do {
			printf("Phone Number	: ");
			rewind(stdin);
			scanf("%s", staff[self].phoneNumber);
			if (!isValidPhone(staff[self].phoneNumber)) {
				printf("Invalid Phone Number\n");
			}
		} while (!isValidPhone(staff[self].phoneNumber));


		do {
			printf("Email		: ");
			rewind(stdin);
			scanf(" %[^\n]", staff[self].email);
			if (!isValidEmail(staff[self].email)) {
				printf("Invalid Email\n");
			}
		} while (!isValidEmail(staff[self].email));


		do {
			printf("Address Line 1	: ");
			rewind(stdin);
			scanf(" %[^\n]", staff[self].address);
			if (!isValidAddress(staff[self].address)) {
				printf("Invalid Address Line 1\n");
			}
		} while (!isValidAddress(staff[self].address));


		do {
			printf("Address Line 2	: ");
			rewind(stdin);
			scanf(" %[^\n]", staff[self].address2);
			if (!isValidAddress2(staff[self].address2)) {
				printf("Invalid Address Line 2\n");
			}
		} while (!isValidAddress2(staff[self].address2));


		do {
			printf("Postal code	: ");
			rewind(stdin);
			scanf("%s", &staff[self].postCode);
			if (!isValidPostCode(staff[self].postCode)) {
				printf("Invalid Postal Code\n");
			}
		} while (!isValidPostCode(staff[self].postCode));


		do {
			printf("State		: ");
			rewind(stdin);
			scanf(" %[^\n]", &staff[self].state);
			if (!isValidState(staff[self].state)) {
				printf("Invalid State\n");
			}
		} while (!isValidState(staff[self].state));
		printf("\n");

		staff[self].salary = 3000.00;
		staff[self].attend = 0;
		staff[self].late = 0;
		staff[self].absent = 0;
		staff[self].totalDaysAttend = 0;
		staff[self].attendanceRate = 0.0;
		staff[self].lateRate = 0.0;
		staff[self].absentRate = 0;
		strcpy(staff[self].lateReason, "no");

		// until this user login step will completer their answer
		for (int j = 0; j < 5; j++) {
			strcpy(staff[self].recovery[j].answer, "");
		}
		break;
	case 2:
		selectFunction();
		break;
	}

	if (temporarySelf >= 0) {
		strcpy(staff[self].id, temporaryID);
	}
	else {
		strcpy(staff[self].id, staffID);
	}

	strcpy(staff[self].password, staff[self].ic);
	printf("\n\n");
	time_t t = time(NULL);
	struct tm date = *localtime(&t);
	printf("Process Successful...\n");
	printf("New account %s signup in %d-%02d-%02d %02d:%02d\n", staff[self].id, date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min);

	staffPtr = fopen("staffFile.bin", "wb");
	if (staffPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	for (int i = 0; i < recordS; i++) {
		fwrite(&staff[i], sizeof(staffDetails), 1, staffPtr);
	}

	fclose(staffPtr);
	free(staff);
	system("pause");
	selectFunction();
}

void sModuleDisplay() {
	FILE* managerPtr, * staffPtr;
	managerPtr = fopen("managerFile.bin", "rb");
	staffPtr = fopen("staffFile.bin", "rb");
	if (managerPtr == NULL || staffPtr == NULL) {
		printf("Unable to open the file\n");
		return;
	}

	management manager;
	staffDetails staff;
	char loginId[6]; //check identity
	char id[6]; //view someone's information
	int i = 0; //count number of manager 
	int found = 0; //check the id exist or not
	int option; //select display what
	int select; //select in details
	int peopleS = 0;
	double totalStaffSalary = 0;
	double avgStaffSalary = 0;
	int totalNumberPeople = 0, male = 0, female = 0, part = 0, full = 0;

	strcpy(loginId, logInID);

	do {
		system("cls");
		printf("Display Table\n");
		printf("-------------------------------------------\n");
		printf("1. Salary\n");
		printf("2. Total Number of people\n");
		printf("3. Total Number of people by gender\n");
		printf("4. Total Number of people by status\n");
		printf("5. Exit\n-------------------------------------------\nSelect your option (1-5) : ");
		rewind(stdin);
		scanf("%d", &option);
		printf("\n");
		if (option < 1 || option>5) {
			printf("Invalid Option\n\n");
		}
	} while (option < 1 || option>5);

	while (fread(&manager, sizeof(management), 1, managerPtr) != 0) {
		if (manager.gender == 'M') {
			male++;
		}
		else if (manager.gender == 'F') {
			female++;
		}
		if (manager.status == 'F') {
			full++;
		}
		else if (manager.status == 'P') {
			part++;
		}
		i++;
	}

	while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
		if (strcmp(staff.name, "DEL") != 0) {
			if (staff.gender == 'M') {
				male++;
			}
			else if (staff.gender == 'F') {
				female++;
			}
			if (staff.status == 'F') {
				full++;
			}
			else if (staff.status == 'P') {
				part++;
			}
			totalStaffSalary += staff.salary;
			peopleS++;
		}
	}

	avgStaffSalary = totalStaffSalary / peopleS;
	totalNumberPeople = i + peopleS;

	rewind(managerPtr); // Rewind file pointer to the beginning
	rewind(staffPtr); // Rewind file pointer to the beginning

	if (loginId[0] == 'M') {
		if (option == 1) {
			do {
				system("cls");
				printf("Salary\n");
				printf("-------------------------------------------\n");
				printf("1. Personal salary\n");
				printf("2. Total staff salary\n");
				printf("3. Average staff salary\n");
				printf("4. Back\n");
				printf("-------------------------------------------\n");
				printf("Select your option (1-4): ");
				rewind(stdin);
				scanf("%d", &select);
			} while (select < 1 || select > 4);
			printf("\n\n");

			system("cls");
			switch (select) {
			case 1:
				if (loginId[0] == 'M') {
					do {
						system("cls");
						printf("Enter the id of the staff you want to see\n");
						printf("--------------------------------------------------\n");
						printf("Enter ID : ");
						rewind(stdin);
						scanf("%s", id);
						id[0] = toupper(id[0]);
						if (id[0] != 'S' || strlen(id) < 4) {
							printf("\n\nInvalid ID\n");
							system("pause");
						}
						printf("\n");
					} while (id[0] != 'S' || strlen(id) < 4);
					printf("\n");

					for (int i = 0; i < S_MAX_SIZE; i++) {
						fread(&staff, sizeof(staffDetails), 1, staffPtr);
						if (strcmp(staff.id, id) == 0) {
							if (strcmp(staff.name, "DEL") == 0) {
								printf("\nThis ID is not exist\n");
								system("pause");
								sModuleDisplay();
							}
							found = 1;
							printf("\nID	: %s\nName	: %s\nSalary	: RM%.2f\n", staff.id, staff.name, staff.salary);
							break;
						}
					}
				}
				break;
			case 2:
			case 3:
				i = 0;
				while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
					found = 1;
					if (i == 0) {
						printf("--------------------------------------------------\n");
						printf("%-7s %-28s %s\n", "ID", "Name", "Salary");
						printf("--------------------------------------------------\n");
					}
					if (strcmp(staff.name, "DEL") != 0) {
						printf("%-7s %-28s RM%.2f\n", staff.id, staff.name, staff.salary);
					}
					i++;
				}
				if (select == 2) {
					printf("\n\nTotal staff salary is RM%.2f\n\n", totalStaffSalary);
				}
				else {
					printf("\n\nAverage staff salary is RM%.2f\n\n", avgStaffSalary);
				}
				break;
			case 4:
				sModuleDisplay();
				break;
			}
		}
		else if (option == 2) {
			do {
				system("cls");
				printf("Total Number of People\n");
				printf("-------------------------------------------\n");
				printf("1. Total number of manager\n");
				printf("2. Total number of staff\n");
				printf("3. Total number of manager and staff\n");
				printf("4. Back\n");
				printf("-------------------------------------------\n");
				printf("Select your option (1-4) : ");
				rewind(stdin);
				scanf("%d", &select);
				if (option < 1 || option > 4) {
					printf("Invalid Option\n\n");
				}
			} while (option < 1 || option > 4);
			system("cls");

			switch (select) {
			case 1:
				i = 0;
				while (fread(&manager, sizeof(management), 1, managerPtr) != 0) {
					found = 1;
					if (i == 0) {
						printf("----------------------------------------------\n");
						printf("%-7s %s\n", "ID", "Name");
						printf("----------------------------------------------\n");
					}
					printf("%-7s %s\n", manager.id, manager.name);
					i++;
				}
				printf("\n\nTotal number of manager is %d\n\n", i);
				break;
			case 2:
				i = 0;
				while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
					found = 1;
					if (i == 0) {
						printf("---------------------------------------------\n");
						printf("%-7s %s\n", "ID", "Name");
						printf("---------------------------------------------\n");
					}
					if (strcmp(staff.name, "DEL") != 0) {
						printf("%-7s %s\n", staff.id, staff.name);
					}
					i++;
				}
				printf("\n\nTotal number of staff is %d\n\n", peopleS);
				break;
			case 3:
				i = 0;
				while (fread(&manager, sizeof(management), 1, managerPtr) != 0) {
					found = 1;
					if (i == 0) {
						printf("-----------------------------------\n");
						printf("	Manager Detail\n");
						printf("-----------------------------------\n");
						printf("%-7s %s\n", "ID", "Name");
					}
					printf("%-7s %s\n", manager.id, manager.name);
					i++;
				}
				printf("\n\n\n");
				i = 0;
				while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
					found = 1;
					if (i == 0) {
						printf("-----------------------------------\n");
						printf("	Staff Detail\n");
						printf("-----------------------------------\n");
						printf("%-7s %s\n", "ID", "Name");
					}
					if (strcmp(staff.name, "DEL") != 0) {
						printf("%-7s %s\n", staff.id, staff.name);
					}
					i++;
				}
				printf("\n\nTotal number of people is %d\n\n", totalNumberPeople);
				break;
			case 4:
				sModuleDisplay();
				break;
			}
		}
		else if (option == 3) {
			do {
				system("cls");
				printf("Gender\n");
				printf("-------------------------------------------\n");
				printf("1. Total number of male\n");
				printf("2. Total number of female\n");
				printf("3. Back\n");
				printf("-------------------------------------------\n");
				printf("Select your option (1-3) : ");
				rewind(stdin);
				scanf("%d", &select);
				printf("\n");
				if (select < 1 || select > 3) {
					printf("Invalid Option\n\n");
				}
			} while (select < 1 || select > 3);

			system("cls");
			switch (select) {
			case 1:
				i = 0;
				while (fread(&manager, sizeof(management), 1, managerPtr) != 0) {
					if (manager.gender == 'M') {
						found = 1;
						if (i == 0) {
							printf("-----------------------------------\n");
							printf("	Manager Detail\n");
							printf("-----------------------------------\n");
							printf("%-8s %-10s %s\n", "ID", "Gender", "Name");
						}
						printf("%-10s %-8c %s\n", manager.id, manager.gender, manager.name);
						i++;
					}
				}
				i = 0;
				while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
					if (staff.gender == 'M') {
						found = 1;
						if (i == 0) {
							printf("\n\n-----------------------------------\n");
							printf("	Staff Detail\n");
							printf("-----------------------------------\n");
							printf("%-8s %-10s %s\n", "ID", "Gender", "Name");
						}
						printf("%-10s %-8c %s\n", staff.id, staff.gender, staff.name);
						i++;
					}
				}
				printf("\n\nTotal number of men is %d\n\n", male);
				break;
			case 2:
				i = 0;
				while (fread(&manager, sizeof(management), 1, managerPtr) != 0) {
					if (manager.gender == 'F') {
						found = 1;
						if (i == 0) {
							printf("-----------------------------------\n");
							printf("	Manager Detail\n");
							printf("-----------------------------------\n");
							printf("%-8s %-10s %s\n", "ID", "Gender", "Name");
						}
						printf("%-10s %-8c %s\n", manager.id, manager.gender, manager.name);
						i++;
					}
				}
				i = 0;
				while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
					if (staff.gender == 'F') {
						found = 1;
						if (i == 0) {
							printf("\n\n-----------------------------------\n");
							printf("	Staff Detail\n");
							printf("-----------------------------------\n");
							printf("%-8s %-10s %s\n", "ID", "Gender", "Name");
						}
						printf("%-10s %-8c %s\n", staff.id, staff.gender, staff.name);
						i++;
					}
				}
				printf("\n\nTotal number of women is %d\n\n", female);
				break;
			case 3:
				sModuleDisplay();
				break;
			}
		}
		else if (option == 4) {
			do {
				system("cls");
				printf("Status\n");
				printf("-------------------------------------------\n");
				printf("1. Total number of full-time\n");
				printf("2. Total number of part-time\n");
				printf("3. Back\n");
				printf("-------------------------------------------\n");
				printf("Select your option (1-3 ): ");
				rewind(stdin);
				scanf("%d", &select);
				printf("\n");
				if (select < 1 || select > 3) {
					printf("Invalid Option\n\n");
				}
			} while (select < 1 || select > 3);
			system("cls");

			switch (select) {
			case 1:
				i = 0;
				while (fread(&manager, sizeof(management), 1, managerPtr) != 0) {
					if (manager.status == 'F') {
						found = 1;
						if (i == 0) {
							printf("-----------------------------------\n");
							printf("	Manager Detail\n");
							printf("-----------------------------------\n");
							printf("%-8s %-10s %s\n", "ID", "Status", "Name");
						}
						printf("%-10s %-8c %s\n", manager.id, manager.status, manager.name);
						i++;
					}
				}
				i = 0;
				while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
					if (staff.status == 'F') {
						found = 1;
						if (i == 0) {
							printf("\n\n-----------------------------------\n");
							printf("	Staff Detail\n");
							printf("-----------------------------------\n");
							printf("%-8s %-10s %s\n", "ID", "Status", "Name");
						}
						printf("%-10s %-8c %s\n", staff.id, staff.status, staff.name);
						i++;
					}
				}
				printf("\n\nTotal number of full-time is %d\n\n", full);
				break;
			case 2:
				i = 0;
				while (fread(&staff, sizeof(staffDetails), 1, staffPtr) != 0) {
					if (staff.status == 'P') {
						found = 1;
						if (i == 0) {
							printf("\n\n-----------------------------------\n");
							printf("	Staff Detail\n");
							printf("-----------------------------------\n");
							printf("%-8s %-10s %s\n", "ID", "Status", "Name");
						}
						printf("%-10s %-8c %s\n", staff.id, staff.status, staff.name);
						i++;
					}
				}
				printf("\n\nTotal number of part-time is %d\n\n", part);
				break;
			case 3:
				sModuleDisplay();
				break;
			}
		}
		else if (option == 5) {
			selectFunction();
		}
	}

	if (!found) {
		printf("No Record Found\n");
	}

	fclose(managerPtr);
	fclose(staffPtr);

	printf("\n\n");
	system("pause");
	sModuleDisplay();
}

void sModuleDelete() {
	FILE* staffPtr, * deletePtr, * storePtr;

	staffDetails* staff = malloc(S_MAX_SIZE * sizeof(staffDetails));
	if (staff == NULL) {
		printf("Memory allocation failed\n");
		return;
	}

	staffDetails temporary;

	char id[5];
	int recordS = 0;
	int s = 0;
	int self = -1; //-1 if id no found
	int option;
	int select;
	int j = 0;

	do {
		system("cls");
		printf("Delete Function\n");
		printf("-------------------------------------------\n");
		printf("1. Delete\n2. View Delete History\n3. Exit\n");
		printf("-------------------------------------------\n");
		printf("Select your option (1-3) : ");
		rewind(stdin);
		scanf("%d", &select);
	} while (select < 1 || select > 3);

	switch (select) {
	case 1:
		staffPtr = fopen("staffFile.bin", "rb");
		if (staffPtr == NULL) {
			printf("Unable to open the file\n");
			return;
		}

		do {
			system("cls");
			printf("Delete Function\n");
			printf("-------------------------------------------\n");
			printf("Enter Staff's ID (X to stop) : ");
			rewind(stdin);
			scanf("%s", id);
			id[0] = toupper(id[0]);
			if (id[0] == 'X') {
				sModuleDelete();
			}
			if (id[0] != 'S' || strlen(id) < 4) {
				printf("\n\nInvalid ID\n");
				system("pause");
			}
		} while (id[0] != 'S' || strlen(id) < 4);


		while (fread(&staff[s], sizeof(staffDetails), 1, staffPtr) != 0) {
			if (strcmp(staff[s].id, id) == 0) {
				self = s;
			}
			s++;
		}
		recordS = s;

		fclose(staffPtr);

		if (strcmp(staff[self].id, id) == 0 && strcmp(staff[self].name, "DEL") != 0) { //prevent id already delete but also can delete again

			do {
				system("cls");
				printf("Confirm Delete ?\n");
				printf("-------------------------------------------\n1. Yes\n2. No\n-------------------------------------------\nSelect your option (1-2) : ");
				rewind(stdin);
				scanf("%d", &option);
			} while (option < 1 || option > 2);

			// store to history file
			if (option == 1) {
				storePtr = fopen("deleteHistory.bin", "ab");
				if (storePtr == NULL) {
					printf("Unable to open the file\n");
					return;
				}
				fwrite(&staff[self], sizeof(staffDetails), 1, storePtr);
				fclose(storePtr);
				// clean data
				memset(staff[self].name, 0, sizeof(staff[self].name));
				strcpy(staff[self].name, "DEL");
				memset(staff[self].ic, 0, sizeof(staff[self].ic));
				strcpy(staff[self].ic, "DEL");
				memset(staff[self].age, 0, sizeof(staff[self].age));
				staff[self].gender = 'D';
				staff[self].status = 'D';
				memset(staff[self].phoneNumber, 0, sizeof(staff[self].phoneNumber));
				strcpy(staff[self].phoneNumber, "DEL");
				memset(staff[self].email, 0, sizeof(staff[self].email));
				strcpy(staff[self].email, "DEL");
				memset(staff[self].address, 0, sizeof(staff[self].address));
				strcpy(staff[self].address, "DEL");
				memset(staff[self].address2, 0, sizeof(staff[self].address2));
				strcpy(staff[self].address2, "DEL");
				memset(staff[self].state, 0, sizeof(staff[self].state));
				strcpy(staff[self].state, "DEL");
				memset(staff[self].postCode, 0, sizeof(staff[self].postCode));
				strcpy(staff[self].postCode, "DEL");
				staff[self].salary = 0;
				memset(staff[self].password, 0, sizeof(staff[self].password));
				strcpy(staff[self].password, "DEL");
				for (int j = 0; j < 5; j++) {
					memset(staff[self].recovery[j].answer, 0, sizeof(staff[self].recovery[j].answer));
					strcpy(staff[self].recovery[j].answer, "DEL");
				}
				staff[self].attend = 0;
				staff[self].late = 0;
				staff[self].absent = 0;
				staff[self].totalDaysAttend = 0;
				staff[self].attendanceRate = 0;
				staff[self].lateRate = 0;
				staff[self].absentRate = 0;
				memset(staff[self].lateReason, 0, sizeof(staff[self].lateReason));
				strcpy(staff[self].lateReason, "DEL");

				// write back all data except deleted data
				deletePtr = fopen("staffFile.bin", "wb");
				if (deletePtr == NULL) {
					printf("Unable to open the file\n");
					return;
				}
				for (int j = 0; j < recordS; j++) {
					fwrite(&staff[j], sizeof(staffDetails), 1, deletePtr);
				}
				fclose(deletePtr);

				printf("\nDELETE Successful\n\n");
			}
			else {
				sModuleDelete();
			}
		}
		else if ((strcmp(staff[self].id, id) == 0 && strcmp(staff[self].name, "DEL") == 0)) {
			printf("\nThis ID already DELETE\n");
			system("pause");
		}
		break;
	case 2:
		system("cls");
		staffPtr = fopen("deleteHistory.bin", "rb");
		if (staffPtr == NULL) {
			printf("Unable to open the file\n");
			return;
		}
		printf("---------------------------------------------------\n");
		printf("                DELETE History\n");
		printf("---------------------------------------------------\n");
		while (fread(&temporary, sizeof(staffDetails), 1, staffPtr) != 0) {
			printf("ID		: %s\n", temporary.id);
			printf("Name		: %s\n", temporary.name);
			printf("IC		: %s\n", temporary.ic);
			printf("Age		: %s\n", temporary.age);
			printf("Gender		: %c\n", temporary.gender);
			printf("Status		: %c\n", temporary.status);
			printf("Phone Number	: %s\n", temporary.phoneNumber);
			printf("Email		: %s\n", temporary.email);
			printf("Address	Line 1	: %s\n", temporary.address);
			printf("Address	Line 2	: %s\n", temporary.address2);
			printf("Postal Code	: %s\n", temporary.postCode);
			printf("State		: %s\n", temporary.state);
			printf("Salary		: RM%.2f\n\n\n", temporary.salary);
			self++;
		}
		fclose(staffPtr);
		break;
	case 3:
		selectFunction();
		break;
	}

	if (self == -1) {
		printf("No Found\n");
	}

	system("pause");
	free(staff);
	sModuleDelete();
}

void confirmPassword(char* password, int* wrongConfirm, bool* continueCreation) {
	char confirm[13];

	do {
		printf("Confirm Password	: ");
		rewind(stdin);
		scanf(" %[^\n]", confirm);

		if (strcmp(password, confirm) != 0) {
			(*wrongConfirm)++;
			if (*wrongConfirm >= 3) {
				printf("\nYou have entered the wrong confirmation password too many times.\n");
				printf("Please create a new password.\n");
				*continueCreation = false;
				return; // Exit the function to restart password creation
			}
			printf("Wrong Password\n\n");
		}
	} while (strcmp(password, confirm) != 0);
	*continueCreation = true;
}

bool isValidName(char* name) {
	for (int i = 0; i < strlen(name); i++) {
		if (!isalpha(name[i]) && name[i] != ' ') {
			return false;
		}
	}
	return true;
}

bool isValidAge(char* age) {
	int len = strlen(age);
	if (!age) {
		return false;
	}

	if (len != 2) {
		return false;
	}

	for (int i = 0; i < len; i++) {
		if (!isdigit(age[i])) {
			return false;
		}
	}

	int ageValue = atoi(age);  // Convert age string to integer
	if (ageValue < 18 || ageValue > 45) {
		return false;
	}

	return true;
}

bool isValidPhone(char* phoneNumber) {
	if (!phoneNumber || strlen(phoneNumber) != 10 || phoneNumber[0] != '0' || phoneNumber[1] != '1') {
		return false;
	}

	for (int i = 0; i < 10; i++) {
		if (!isdigit(phoneNumber[i]))
			return false;
	}

	return true;
}

bool isValidAddress(char* address) {
	int len = strlen(address);
	bool hasDigit = false, hasAlpha = false;
	char ch;

	if (!address || len < 10) {
		return false;
	}

	if (!isalnum(address[0]) || !isalnum(address[len - 1])) {
		return false; // First or last character is a special character
	}

	for (int i = 0; i < len; i++) {
		ch = address[i];
		if (isdigit(ch)) {
			hasDigit = true;  // Check for at least one numeric character.
		}
		else if (isalpha(ch)) {
			hasAlpha = true;  // Check for at least one alphabetic character.
		}
		else if (!isspace(ch) && ch != ',' && ch != '.' && ch != '-' && ch != '/') {
			return false;  // Ensure only valid separators and characters are used.
		}
	}

	if (!hasDigit) {
		return false;
	}

	if (!hasAlpha) {
		return false;
	}

	return true;
}

bool isValidAddress2(char* address2) {
	int len = strlen(address2);
	bool hasValidCharacter = false, hasAlpha = false;

	if (!address2 || len < 5) {
		return false;
	}

	if (!isalnum(address2[0]) || !isalnum(address2[len - 1])) {
		return false; // First or last character is a special character
	}

	for (int i = 0; i < len; i++) {
		char ch = address2[i];
		if (isalnum(ch) || isspace(ch) || ch == ',' || ch == '.' || ch == '-' || ch == '/') {
			// Valid character
			if (isalpha(ch)) {
				hasAlpha = true;  // Check for at least one alphabetic character.
			}
		}
		else {
			// Invalid character
			return false;
		}
	}

	if (!hasAlpha) {
		return false;
	}

	return true;
}

bool isValidPostCode(char* postCode) {
	int len = strlen(postCode);

	if (!postCode || len != 5) {
		return false;
	}

	for (int i = 0; i < 5; i++) {
		if (!isdigit(postCode[i]))
			return false;
	}

	return true;
}

bool isValidState(char* state) {
	int alphaCount = 0;
	int len = strlen(state);

	if (!state || len < 5 || len > 15) {
		return false;
	}

	for (int i = 0; i < len; i++) {
		if (!isalpha(state[i]) && state[i] != ' ') {
			return false;
		}
	}

	return true;
}

bool isValidEmail(char* email) {
	int countAt = 0;
	int countDot = 0;
	int len = strlen(email);
	char ch;
	int countDotAfterAt = 0;
	bool atSeen = false;
	char* check;

	if (!email || len == 0) {
		return false;
	}

	if (email[0] == '.' || email[0] == '@' || email[0] == '-' ||
		email[len - 1] == '.' || email[len - 1] == '@' || email[len - 1] == '-') {
		return false;
	}

	for (int i = 0; i < len; i++) {
		ch = email[i];

		if (isspace(ch)) {
			return false;
		}

		if (ch == '@') {
			countAt++;
			if (countAt > 1 || i == 0 || i == len - 1) { // '@' should be neither first nor last, nor appear more than once
				return false;
			}
			atSeen = true; // Start validation of domain part
		}
		else if (!atSeen) { //check character before @ 
			if (!isalnum(ch) && ch != '.' && ch != '-' && ch != '_' && ch != '+') {
				return false;
			}
			if (ch == '.' && email[i + 1] == '.') { // Consecutive dots in local part
				return false;
			}
		}
		else {
			// Validate domain part after '@'
			if (!isalnum(ch) && ch != '-' && ch != '.') {
				return false;
			}
			if (ch == '.') {
				countDotAfterAt++;
				if (email[i + 1] == '.') { // Consecutive dots in domain part
					return false;
				}
			}
		}
	}
	if (countAt != 1) {
		return false;
	}

	check = &email[len - 3];
	if (strcmp(check, ".my") != 0 && strcmp(check - 1, ".com") != 0) {
		return false;
	}

	return true;
}

bool isValidIC(char* ic) {
	if (!ic) {
		return false;
	}

	if (strlen(ic) != 12) {
		return false;
	}

	// check year is start from 79( 45 age) to 06 ( 18 age)
	if (!((strncmp(ic, "79", 2) >= 0 && strncmp(ic, "99", 2) <= 0) || (strncmp(ic, "00", 2) >= 0 && strncmp(ic, "06", 2) <= 0))) {
		return false;
	}

	for (int i = 0; i < 12; i++) {
		if (!isdigit(ic[i]))
			return false;
	}

	// check month
	if (ic[2] == '1' && ic[3] > '2') {
		return false;
	}

	// check january
	if (ic[2] == '0' && ic[3] == '1') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '1')) {
			return false;
		}
	}

	// check febuary
	if (ic[2] == '0' && ic[3] == '2') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '2' || (ic[4] == '2' && ic[5] > '9')) {
			return false;
		}
	}

	// check march
	if (ic[2] == '0' && ic[3] == '3') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '1')) {
			return false;
		}
	}

	// check april
	if (ic[2] == '0' && ic[3] == '4') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '0')) {
			return false;
		}
	}

	// check may
	if (ic[2] == '0' && ic[3] == '5') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '1')) {
			return false;
		}
	}

	// check june
	if (ic[2] == '0' && ic[3] == '6') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '0')) {
			return false;
		}
	}

	// check july
	if (ic[2] == '0' && ic[3] == '7') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '1')) {
			return false;
		}
	}

	// check august
	if (ic[2] == '0' && ic[3] == '8') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '1')) {
			return false;
		}
	}

	// check september
	if (ic[2] == '0' && ic[3] == '9') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '0')) {
			return false;
		}
	}

	// check october
	if (ic[2] == '1' && ic[3] == '0') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '1')) {
			return false;
		}
	}

	// check november
	if (ic[2] == '1' && ic[3] == '1') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '0')) {
			return false;
		}
	}

	// check december
	if (ic[2] == '1' && ic[3] == '2') {
		if (ic[4] == '0' && ic[5] == '0') {
			return false;
		}
		if (ic[4] > '3' || (ic[4] == '3' && ic[5] > '1')) {
			return false;
		}
	}

	return true;
}

bool isValidPassword(char* password) {
	if (!password) {
		return false;
	}

	if (strlen(password) < 8 || strlen(password) > 12) {
		return false;
	}

	for (int i = 0; i < strlen(password); i++) {
		if (password[i] == ' ') {
			return false;
		}
	}

	return true;
}

// Member Module Function
bool idValidation(char* memberID) {
	MemberInfo temp;
	bool length = true;
	bool valid = true;

	if (strlen(memberID) >= 20) {
		length = false;
	}

	FILE* validPtr;
	validPtr = fopen("member_detail.txt", "r");
	if (validPtr == NULL) {
		printf("Unable to open file...\n");
		exit(-1);
	}
	while (fscanf(validPtr, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp.memberID, temp.password,
		temp.name, &temp.age, &temp.gender, temp.ic, temp.phoneNo, temp.email, temp.recovery.q1, temp.recovery.q2,
		temp.recovery.q3) != EOF) {
		if (strcmp(memberID, temp.memberID) == 0) {
			valid = false;
			break;
		}
	}

	if (!length) {
		printf("Member ID shouldn't be longer than 20 characters\n");
		printf("\n");
	}
	if (!valid) {
		printf("Member ID is taken...\n");
		printf("\n");
	}
	fclose(validPtr);

	return length && valid;
}

bool icValidation(char* ic) {
	MemberInfo temp;
	bool length = false;
	bool valid = true;
	FILE* validPtr;
	validPtr = fopen("member_detail.txt", "r");
	if (validPtr == NULL) {
		printf("Unable to open file...\n");
		exit(-1);
	}

	while (fscanf(validPtr, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp.memberID, temp.password,
		temp.name, &temp.age, &temp.gender, temp.ic, temp.phoneNo, temp.email, temp.recovery.q1, temp.recovery.q2,
		temp.recovery.q3) != EOF) {
		if (strcmp(member.ic, temp.ic) == 0) {
			valid = false;
			break;
		}
	}
	if (strlen(ic) == 12) {
		length = true;
	}
	else {
		printf("Invalid IC number length. Please try again. (12 numbers only)\n");
	}

	if (!valid) {
		printf("This IC number is already registered\n\n");
	}
	return length && valid;
}

bool phoneNovalidation(char* phoneNo) {
	MemberInfo temp;
	bool length = false;
	bool valid = true;
	FILE* validPtr;
	validPtr = fopen("member_detail.txt", "r");
	if (validPtr == NULL) {
		printf("Unable to open file...\n");
		exit(-1);
	}

	while (fscanf(validPtr, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp.memberID, temp.password,
		temp.name, &temp.age, &temp.gender, temp.ic, temp.phoneNo, temp.email, temp.recovery.q1, temp.recovery.q2,
		temp.recovery.q3) != EOF) {
		if (strcmp(member.phoneNo, temp.phoneNo) == 0) {
			valid = false;
			break;
		}
	}

	if (strlen(phoneNo) == 9 || strlen(phoneNo) == 10 || strlen(phoneNo) == 11) {
		length = true;
	}
	else {
		printf("Incorrect format. Please try again.\n");
	}

	if (!valid) {
		printf("This phone Number is already registered\n\nw");
	}

	return length && valid;
}

bool passwordValidation(char* password) {
	bool alpha = false;
	bool digit = false;
	bool length = false;
	for (int i = 0; password[i] != '\0'; i++) {
		if (isalpha(password[i])) {
			alpha = true;
		}
		else if (isdigit(password[i])) {
			digit = true;
		}
	}
	if (strlen(password) < 20) {
		length = true;
	}
	if (!alpha) {
		printf("Password must contain alphabets.\n");
	}
	else if (!digit) {
		printf("Password must contain numbers.\n");
	}
	else if (!length) {
		printf("Password shouldn't exceed 20 characters.\n");
	}
	return alpha && digit && length;
}

bool emailValidation(char* email) {
	MemberInfo temp;
	bool firstLetter = false;
	bool symbol = false;
	bool valid = true;
	FILE* validPtr;
	validPtr = fopen("member_detail.txt", "r");
	if (validPtr == NULL) {
		printf("Unable to open file...\n");
		exit(-1);
	}

	while (fscanf(validPtr, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp.memberID, temp.password,
		temp.name, &temp.age, &temp.gender, temp.ic, temp.phoneNo, temp.email, temp.recovery.q1, temp.recovery.q2,
		temp.recovery.q3) != EOF) {
		if (strcmp(member.email, temp.email) == 0) {
			valid = false;
			break;
		}
	}

	if (isalpha(email[0])) {
		firstLetter = true;
	}
	for (int i = 0; email[i] != NULL; i++) {
		if (email[i] == '@') {
			symbol = true;
		}
	}
	if (!firstLetter) {
		printf("First letter of email must start with an alphabet.\n");
	}
	else if (!symbol) {
		printf("Invalid email format.\n");
	}

	else if (!valid) {
		printf("This email is already registered\n\n");
	}
	return firstLetter && symbol && valid;
}

void memberLogin(MemberInfo* profile) {
	GetLocalTime(&t);
	FILE* memberActivity;
	memberActivity = fopen("member_activity.txt", "a");
	if (memberActivity == NULL) {
		printf("Unable to open file...\n");
		exit(-1);
	}

	fprintf(memberActivity, "%s|%02d/%02d/%d %02d:%02d:%02d|%s\n",
		(*profile).memberID, t.wDay, t.wMonth, t.wYear,
		t.wHour, t.wMinute, t.wSecond, "Login");

	fclose(memberActivity);

	return;
}

void memberSignUp(MemberInfo* member) {
	GetLocalTime(&t);
	FILE* memberActivity;
	memberActivity = fopen("member_activity.txt", "a");
	if (memberActivity == NULL) {
		printf("Unable to open file...\n");
		exit(-1);
	}

	fprintf(memberActivity, "%s|%02d/%02d/%d %02d:%02d:%02d|%s\n",
		(*member).memberID, t.wDay, t.wMonth, t.wYear,
		t.wHour, t.wMinute, t.wSecond, "SignUp");

	fclose(memberActivity);

	return;
}

// clear screen
void clearScreen() {
	system("cls");
}

// Main 
int mModuleMain() {
	int option;
	do {
		clearScreen();
		printf("Welcome!\n");
		printf("------------------------------\n");
		printf("1. Login\n");
		printf("2. Signup\n");
		printf("3. Password Recovery\n");
		printf("4. Exit\n");
		printf("------------------------------\n");
		printf("Select an option (1 - 4): ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 4) {
			rewind(stdin);
			option = 0;
		}
		rewind(stdin);

		switch (option) {
		case 1: mModuleLogin(); break;
		case 2: mModuleSignup(); break;
		case 3: mPasswordRecovery(); break;
		case 4: main(); break;
		default: printf("Invalid option. Please try again.\n"); system("pause");
		}
	} while (option == 0);
	return 0;
}

// login
void mModuleLogin() {
	MemberInfo profile;
	GetLocalTime(&t);
	int option = 0;
	int i = 0;
	mFile = fopen("member_detail.txt", "r");
	rewind(mFile);
	if (mFile == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}
	rewind(mFile);

	char id[20], password[20];
	bool loggedIn = false;

	clearScreen();
	do {
		printf("LOG IN\n");
		printf("------------------------------\n");
		printf("Member ID : ");
		scanf("%s", &id);
		rewind(stdin);

		printf("Password  : ");
		scanf("%s", &password);
		rewind(stdin);

		while (fscanf(mFile, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", profile.memberID, profile.password, profile.name, &profile.age, &profile.gender,
			profile.ic, profile.phoneNo, profile.email, profile.recovery.q1, profile.recovery.q2, profile.recovery.q3) != EOF) {
			if (strcmp(id, profile.memberID) == 0 && strcmp(password, profile.password) == 0) {
				loggedIn = true;
				break;
			}
			i++;
		}

		if (loggedIn) {
			printf("Login successful. Welcome %s - %d-%d-%d %d:%d:%d\n\n", profile.name, t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);
			system("pause");
			memberLogin(&profile);
			readFile(&profile);
		}
		else {
			do {
				printf("Invalid Member ID or Password.\n");
				printf("----------------------------------------\n");
				printf("1. Try again?\n");
				printf("2. Forget password?\n");
				printf("3. Return to main menu?\n");
				printf("----------------------------------------\n");
				printf("Please choose an option (1 - 3) : ");
				rewind(stdin);
				if (scanf("%d", &option) != 1 || option < 1 || option > 3) {
					rewind(stdin);
					option = 0;
				}

				switch (option) {
				case 1: mModuleLogin(); break;
				case 2: mPasswordRecovery(); break;
				case 3: mModuleMain(); break;
				default: printf("Invalid option. Please try again.\n");
				}
			} while (option == 0);

			rewind(mFile);
		}
	} while (!loggedIn);

	fclose(mFile);
}

// signup
void mModuleSignup() {
	char pwConfirm[20];

	clearScreen();

	printf("SIGN UP\n");
	printf("--------------------------------------------\n");
	// Member ID
	do {
		rewind(stdin);
		printf("Enter member ID (X to exit): ");
		scanf("%s", &member.memberID);
		if (strcmp(member.memberID, "x") == 0 || strcmp(member.memberID, "X") == 0) {
			mModuleMain();
		}
	} while (!idValidation(member.memberID));
	printf("\n");

	do {
		rewind(stdin);
		printf("Enter password: ");
		scanf("%s", &member.password);
		rewind(stdin);

		printf("Confirm password: ");
		scanf("%s", &pwConfirm);


		if (strcmp(member.password, pwConfirm) != 0) {
			printf("Password does not match. Please try again.\n");
			printf("\n");
		}

	} while (!passwordValidation(member.password) || strcmp(member.password, pwConfirm) != 0);
	printf("\n");

	rewind(stdin);
	printf("Enter Name: ");
	scanf("%[^\n]", &member.name);
	printf("\n");

	// Age
	do {
		printf("Enter Age (18 - 100): ");
		if (scanf("%d", &member.age) != 1) {
			rewind(stdin);
			printf("Please enter digit only. \n");
		}

		else if (member.age < 18) {
			printf("You need to be atleast 18 years old\n");
		}
	} while (member.age < 18);
	printf("\n");
	// Gender
	do {
		rewind(stdin);
		printf("Enter Gender (M = Male | F = Female): ");
		scanf("%c", &member.gender);
		printf("\n");

		// Try again if input is not M or F
		member.gender = toupper(member.gender);
		if (member.gender != 'M' && member.gender != 'F') {
			printf("Invalid Input. Please try again. M for male, F for female\n");
		}
	} while (member.gender != 'M' && member.gender != 'F');

	// IC
	do {
		rewind(stdin);
		printf("Enter identification card number (12 numbers): ");
		scanf("%s", &member.ic);
	} while (!icValidation(member.ic));
	printf("\n");

	// phone Number
	do {
		rewind(stdin);
		printf("Enter Phone Number: ");
		scanf("%s", &member.phoneNo);
	} while (!phoneNovalidation(member.phoneNo));
	printf("\n");

	// email
	do {
		printf("Enter E-mail: ");
		scanf("%s", &member.email);
	} while (!emailValidation(member.email));
	printf("\n");

	// recovery question
	rewind(stdin);
	printf("Please answer a few questions to proceed\n");
	printf("These question will be used to recover your password\n");
	printf("incase you forget ur password\n");
	printf("1. What is your hobby: ");
	scanf(" %[^\n]", &mRecovery.q1);

	rewind(stdin);
	printf("2. What is your first car: ");
	scanf(" %[^\n]", &mRecovery.q2);

	rewind(stdin);
	printf("3. What is your favourite colour: ");
	scanf(" %[^\n]", &mRecovery.q3);

	mFile = fopen("member_detail.txt", "a");
	if (mFile == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}

	//write new member detail to text file
	fprintf(mFile, "%s|%s|%s|%d|%c|%s|%s|%s|%s|%s|%s\n",
		member.memberID, member.password, member.name, member.age, member.gender,
		member.ic, member.phoneNo, member.email, mRecovery.q1, mRecovery.q2, mRecovery.q3);

	fclose(mFile);

	GetLocalTime(&t);
	printf("Account successfully created. - %d-%d-%d %d:%d:%d\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);
	memberSignUp(&member);
	system("pause");
	// Return to main menu

	mModuleMain();
}

// password recovery
void mPasswordRecovery() {
	clearScreen();
	MemberInfo temp[MAX_SIZE];
	MemberInfo new;
	int i = 0;
	char pwConfirm[20];

	// Enter ID 
	printf("Enter your ID (X to exit): ");
	scanf("%s", new.memberID);
	if (strcmp(new.memberID, "x") == 0 || strcmp(new.memberID, "X") == 0) {
		mModuleMain();
	}

	FILE* read;
	read = fopen("member_detail.txt", "r");
	if (read == NULL) {
		printf("Unable to open file\n");
		exit(-1);
	}
	while (fscanf(read, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp[i].memberID, temp[i].password,
		temp[i].name, &temp[i].age, &temp[i].gender, temp[i].ic, temp[i].phoneNo, temp[i].email, temp[i].recovery.q1, temp[i].recovery.q2,
		temp[i].recovery.q3) != EOF) {
		i++;
	}
	fclose(read);

	// if ID match prompt user to answer recovery question
	for (int y = 0; y < i; y++) {
		if (strcmp(new.memberID, temp[y].memberID) == 0) {
			rewind(stdin);
			printf("\nAnswer these questions to recover your password\n");
			printf("What is your hobby: ");
			scanf("%[^\n]", &new.recovery.q1);

			rewind(stdin);
			printf("What is your first car: ");
			scanf("%[^\n]", &new.recovery.q2);

			rewind(stdin);
			printf("What is your favourite colour: ");
			scanf("%[^\n]", &new.recovery.q3);

			// if question answer correctly let user reset their password
			if (strcmp(new.recovery.q1, temp[y].recovery.q1) == 0 && strcmp(new.recovery.q2, temp[y].recovery.q2) == 0
				&& strcmp(new.recovery.q3, temp[y].recovery.q3) == 0) {
				do {
					rewind(stdin);
					printf("\nReset password\n");
					printf("New password: ");
					scanf("%s", new.password);
					rewind(stdin);
					printf("Confirm new password: ");
					scanf("%s", pwConfirm);

					if (strcmp(new.password, pwConfirm) != 0) {
						printf("Password does not match. Please try again.\n");
						rewind(stdin);
					}
				} while (!passwordValidation(new.password) || strcmp(new.password, pwConfirm) != 0);

				memset(temp[y].password, 0, sizeof(temp[y].password));
				strcpy(temp[y].password, new.password);
				printf("Password successfully changed\n");

				// rewrite the updated password into text file
				FILE* write;
				write = fopen("member_detail.txt", "w");
				if (write == NULL) {
					printf("Unable to open file\n");
					exit(-1);
				}

				for (int x = 0; x < i; x++) {
					fprintf(write, "%s|%s|%s|%d|%c|%s|%s|%s|%s|%s|%s\n",
						temp[x].memberID, temp[x].password, temp[x].name, temp[x].age, temp[x].gender,
						temp[x].ic, temp[x].phoneNo, temp[x].email, temp[x].recovery.q1, temp[x].recovery.q2, temp[x].recovery.q3);
				}

				fclose(write);

				printf("Returning to main menu\n");
				system("pause");
				mModuleMain();
			}

			else {
				// if question answer incorrectly
				printf("You are not eligible to recover your account.\n");
				printf("Returning to Menu\n");
				system("pause");
				mModuleMain();
			}

		}
	}

	// if ID doesn't match any data in the text file
	int option;
	do {
		printf("Member ID not found.\n");
		printf("1. Try again?\n");
		printf("2. Menu\n");
		printf("--------------------\n");
		printf("choose an option: ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
			rewind(stdin);
			option = 0;
		}

		switch (option) {
		case 1: mPasswordRecovery(); break;
		case 2: mModuleMain(); break;
		default: printf("Invalid option...\n");
		}
	} while (1);
}

void readFile(MemberInfo* profile) {
	MemberInfo read;
	mFile = fopen("member_detail.txt", "r");
	if (mFile == NULL) {
		printf("Unable to open file");
		exit(-1);
	}

	while (fscanf(mFile, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", read.memberID, read.password,
		read.name, &read.age, &read.gender, read.ic, read.phoneNo, read.email, read.recovery.q1, read.recovery.q2,
		read.recovery.q3) != EOF) {
		if (strcmp(read.memberID, (*profile).memberID) == 0) {
			break;
		}
	}
	fclose(mFile);
	menu(&read);
}

// member's main menu
void menu(MemberInfo* read) {
	clearScreen();
	int option;
	do {
		clearScreen();
		printf("MEMBER MENU\n");
		printf("----------------------\n");
		printf("1. View profile\n");
		printf("2. Modify profile\n");
		printf("3. Delete Account\n");
		printf("4. Ticket Booking\n");
		printf("5. Sign out\n");
		printf("----------------------\n");
		printf("Select an option: ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 5) {
			rewind(stdin);
			option = 0;
		}
		switch (option) {
		case 1: displayMember(read); break;
		case 2: modifyMember(read); break;
		case 3: deleteMemberMenu(read); break;
		case 4: ticketBookingMenu(); break;
		case 5: mModuleMain(); break;
		default: printf("Invalid option. Please try again.\n");
		}
	} while (1);
	system("pause");
}

// member profile
void displayMember(MemberInfo* read) {
	clearScreen();
	printf("YOUR PROFILE\n");
	printf("-----------------------------------------\n");
	printf("Member ID : %s\n", (*read).memberID);
	printf("Name      : %s\n", (*read).name);
	printf("IC        : %s\n", (*read).ic);
	printf("Age       : %d\n", (*read).age);
	printf("Gender    : %c\n", (*read).gender);
	printf("Email     : %s\n", (*read).email);
	printf("Phone no. : %s\n", (*read).phoneNo);
	printf("------------------------------------------\n");
	printf("\n");
	printf("Back to menu\n");
	system("pause");
	clearScreen();
	menu(read);
}

void modifyMember(MemberInfo* read) {
	int option;
	int i = 0;
	MemberInfo input;
	MemberInfo temp[MAX_SIZE];

	mFile = fopen("member_detail.txt", "r");
	if (mFile == NULL) {
		printf("Unable to open file\n");
		exit(-1);
	}

	while (fscanf(mFile, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp[i].memberID, temp[i].password, temp[i].name, &temp[i].age, &temp[i].gender,
		temp[i].ic, temp[i].phoneNo, temp[i].email, temp[i].recovery.q1, temp[i].recovery.q2, temp[i].recovery.q3) != EOF) {
		if (strcmp(temp[i].memberID, (*read).memberID) == 0) {
			do {
				clearScreen();
				//menu
				printf("MODIFY PROFILE\n");
				printf("-------------------------------\n");
				printf("What do you want to modify\n");
				printf("1. Password\n");
				printf("2. Name\n");
				printf("3. Age\n");
				printf("4. Gender\n");
				printf("5. Ic Number\n");
				printf("6. Phone Number\n");
				printf("7. Email\n");
				printf("8. Password Recovery Detail\n");
				printf("9. Back to menu\n");
				printf("-------------------------------\n");
				printf("Choose an option : ");
				if (scanf("%d", &option) != 1 || option < 1 || option > 9) {
					rewind(stdin);
					option = 0;
				}

				//verify user by entering their current password to change new password
				switch (option) {
				case 1:
					do {
						clearScreen();
						printf("MODIFY PASSWORD\n");
						printf("--------------------------------------------------\n");
						printf("Please enter your current password: ");
						scanf("%s", &input.password);
						rewind(stdin);
						if (strcmp(input.password, temp[i].password) == 0) {
							modifyPassword(temp[i].password);
							printf("new password = %s", temp[i].password);
							printf("Password modify successfully\n");
							system("pause");
							break;
						}
						else {
							int retry;
							do {
								//if current password is incorrect
								printf("Password does not match.\n");
								printf("1. Try again?\n");
								printf("2. Forgot Password?\n");
								printf("3. Return to menu\n");
								printf("--------------------------\n");
								printf("Enter an option : ");
								if (scanf("%d", &retry) != 1 || retry < 1 || retry > 3) {
									rewind(stdin);
									retry = 0;
								}

								switch (retry) {
								case 1: break;
								case 2: mPasswordRecovery(); break;
								case 3: menu(read); break;
								default: printf("Invalid option...\n");
								}
							} while (retry == 0);
						}
					} while (1);
					break;
				case 2:
					// modify name
					clearScreen();
					rewind(stdin);
					printf("MODIFY NAME\n");
					printf("------------------------------------\n");
					printf("Enter New name: ");
					scanf("%[^\n]", &input.name);
					memset(temp[i].name, 0, sizeof(temp[i].name));
					strcpy(temp[i].name, input.name);
					printf("Name modify successfully\n");
					system("pause");
					break;

				case 3:
					do {
						// modify age
						clearScreen();
						printf("MODIFY AGE\n");
						printf("-------------------------\n");
						printf("Enter new Age : ");
						if (scanf("%d", &input.age) != 1) {
							rewind(stdin);
							printf("Please enter digit only. \n");
							system("pause");
						}
						else if (input.age < 18) {
							printf("You need to be atleast 18 years old\n");
							system("pause");
						}
					} while (input.age < 18);
					temp[i].age = input.age;
					printf("Age modify successfully\n");
					system("pause");
					break;

				case 4:
					// modify gender
					do {
						clearScreen();
						rewind(stdin);
						printf("MODIFY GENDER\n");
						printf("--------------------------------------------\n");
						printf("Edit Gender (M = male || F = female) : ");
						scanf("%c", &input.gender);
						input.gender = toupper(input.gender);
						if (input.gender != 'M' && input.gender != 'F') {
							printf("Invalid Input. Try again. M for male and F for female");
						}
					} while (input.gender != 'M' && input.gender != 'F');

					temp[i].gender = input.gender;
					printf("Gender modify successfully\n");
					system("pause");
					break;

				case 5:
					// modify ic number
					do {
						clearScreen();
						rewind(stdin);
						printf("MODIFY IC\n");
						printf("---------------------------------------\n");
						printf("Enter new IC Number : ");
						scanf("%s", &input.ic);
					} while (!icValidation(input.ic));
					memset(temp[i].ic, 0, sizeof(temp[i].ic));
					strcpy(temp[i].ic, input.ic);
					printf("IC number modify successfully\n");
					system("pause");
					break;

				case 6:
					// modify phone number
					do {
						clearScreen();
						printf("MODIFY PHONE NO.\n");
						printf("--------------------------------------\n");
						rewind(stdin);
						printf("Enter new Phone Number : ");
						scanf("%s", &input.phoneNo);
					} while (!phoneNovalidation(input.phoneNo));
					memset(temp[i].phoneNo, 0, sizeof(temp[i].phoneNo));
					strcpy(temp[i].phoneNo, input.phoneNo);
					printf("Phone number modify successfully\n");
					system("pause");
					break;

				case 7:
					// modify email
					do {
						clearScreen();
						rewind(stdin);
						printf("MODIFY EMAIL\n");
						printf("-------------------------------------\n");
						printf("Enter new Email : ");
						scanf("%s", &input.email);
					} while (!emailValidation(input.email));
					memset(temp[i].email, 0, sizeof(temp[i].email));
					strcpy(temp[i].email, input.email);
					printf("Email modify successfully\n");
					system("pause");
					break;

				case 8:
					// modify recovery question
					modifyRecovery(&temp, i, read);
					break;

				case 9:
					// back to menu
					menu(read);
					break;

				default:
					printf("Invalid option.\n");
				}

			} while (option != 9);

		}
		i++;
	}

	fclose(mFile);

	FILE* upd;
	upd = fopen("member_detail.txt", "w");
	if (upd == NULL) {
		printf("Unable to open file");
		exit(-1);
	}


	for (int y = 0; y < i; y++) {
		fprintf(upd, "%s|%s|%s|%d|%c|%s|%s|%s|%s|%s|%s\n",
			temp[y].memberID, temp[y].password, temp[y].name, temp[y].age, temp[y].gender,
			temp[y].ic, temp[y].phoneNo, temp[y].email, temp[y].recovery.q1, temp[y].recovery.q2,
			temp[y].recovery.q3);
	}

	fclose(upd);

	readFile(read);
}

void modifyPassword(char* newPassword) {
	char confirm[30];
	do {
		//new password
		printf("\n");
		printf("Enter new password : ");
		scanf("%s", newPassword);
		rewind(stdin);

		printf("Confirm new password : ");
		scanf("%s", confirm);
		rewind(stdin);

		if (strcmp(newPassword, confirm) != 0) {
			printf("Password does not match");
		}
	} while (!passwordValidation(newPassword) || strcmp(newPassword, confirm) != 0);
}

// modify recovery question's answer
void modifyRecovery(MemberInfo temp[], int i, MemberInfo* read) {
	int option;
	char newAnswer[20];

	do {
		clearScreen();
		printf("MODIFY RECOVERY DETAIL\n");
		printf("--------------------------------------------------------------\n");
		printf("1. What is your hobby : %s\n", (*read).recovery.q1);
		printf("2. What is your first car : %s\n", (*read).recovery.q2);
		printf("3. What is your favourite colour : %s\n", (*read).recovery.q3);
		printf("4. Exit\n");
		printf("Which recovery answer you want to change\n");
		printf("--------------------------------------------------------------\n");
		printf("Choose an option (1-4) : ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 4) {
			rewind(stdin);
			option = 0;
		}


		switch (option) {
		case 1:
			rewind(stdin);
			printf("Answer Question 1 again\n");
			printf("What is your hobby : ");
			scanf("%[^\n]", &newAnswer);
			memset(temp[i].recovery.q1, 0, sizeof(temp[i].recovery.q1));
			strcpy(temp[i].recovery.q1, newAnswer);
			printf("Question 1 answer successfully modified\n");
			system("pause");
			modifyMember(read);

		case 2:
			rewind(stdin);
			printf("Answer Question 2 again\n");
			printf("What is your first car : ");
			scanf("%[^\n]", &newAnswer);
			memset(temp[i].recovery.q2, 0, sizeof(temp[i].recovery.q2));
			strcpy(temp[i].recovery.q2, newAnswer);
			printf("Question 2 answer successfully modified\n");
			system("pause");
			modifyMember(read);

		case 3:
			rewind(stdin);
			printf("Answer Question 3 again\n");
			printf("What is your favourite colour : ");
			scanf("%[^\n]", &newAnswer);
			memset(temp[i].recovery.q3, 0, sizeof(temp[i].recovery.q3));
			strcpy(temp[i].recovery.q3, newAnswer);
			printf("Question 3 answer successfully modified\n");
			system("pause");
			modifyMember(read);

		case 4:
			modifyMember(read); break;

		default:
			printf("Invalid option. Please try again\n");
		}

	} while (option != 1 || option < 1 || option > 4);
}

// delete member's account
void deleteMemberMenu(MemberInfo* read) {
	char confirmation[8];

	do {
		clearScreen();
		int option;
		printf("DELETE ACCOUNT\n");
		printf("-----------------------------------\n");
		printf("Do you want to DELETE your account?\n");
		printf("1. Yes\n");
		printf("2. Back to menu\n");
		printf("-----------------------------------\n");
		printf("Choose an option : ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
			rewind(stdin);
			option = 0;
		}

		switch (option) {
		case 1:
			do {
				printf("Are you sure you want to DELETE your account?\n");
				printf("Type the \"CONFIRM\" to continue / or \"STOP\" to stop the process\n");
				scanf("%s", &confirmation);

				for (int i = 0; confirmation[i] != '\0'; i++) {
					confirmation[i] = toupper(confirmation[i]);
				}

				if (strcmp(confirmation, "CONFIRM") == 0) {
					deleteMember(read);
				}
				else if (strcmp(confirmation, "STOP") == 0) {
					menu(read);
				}
				else {
					printf("Invalid keyword. Please try again\n");
				}
			} while (1);
			break;
		case 2: menu(read); break;
		default: printf("Invalid option...\n");
		}
	} while (1);

}

void deleteMember(MemberInfo* read) {
	GetLocalTime(&t);
	MemberInfo temp[MAX_SIZE];
	FILE* readPtr;
	readPtr = fopen("member_detail.txt", "r");
	if (readPtr == NULL) {
		printf("Unable to open file\n");
		exit(-1);
	}

	int i = 0;
	//read file
	while (fscanf(readPtr, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp[i].memberID, temp[i].password, temp[i].name,
		&temp[i].age, &temp[i].gender, temp[i].ic, temp[i].phoneNo, temp[i].email, temp[i].recovery.q1, temp[i].recovery.q2,
		temp[i].recovery.q3) != EOF) {
		i++;
	}

	fclose(readPtr);

	FILE* deletePtr;
	deletePtr = fopen("member_detail.txt", "w");
	if (deletePtr == NULL) {
		printf("Unable to open file\n");
		exit(-1);
	}

	//replace file data after deletion of data
	for (int y = 0; y < i; y++) {
		if (strcmp(temp[y].memberID, (*read).memberID) != 0) {
			fprintf(deletePtr, "%s|%s|%s|%d|%c|%s|%s|%s|%s|%s|%s\n",
				temp[y].memberID, temp[y].password, temp[y].name, temp[y].age, temp[y].gender,
				temp[y].ic, temp[y].phoneNo, temp[y].email, temp[y].recovery.q1, temp[y].recovery.q2,
				temp[y].recovery.q3);
		}
	}

	printf("Delete Successful. - %d-%d-%d %d:%d:%d\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);
	system("pause");
	fclose(deletePtr);

	FILE* backupPtr;
	backupPtr = fopen("deleted_backup.txt", "w");
	if (backupPtr == NULL) {
		printf("Unable to open file\n");
		exit(-1);
	}

	//deleted account backup file
	for (int x = 0; x < i; x++) {
		if (strcmp(temp[x].memberID, (*read).memberID) == 0)
			fprintf(deletePtr, "%s|%s|%s|%d|%c|%s|%s|%s|%s|%s|%s\n",
				temp[x].memberID, temp[x].password, temp[x].name, temp[x].age, temp[x].gender,
				temp[x].ic, temp[x].phoneNo, temp[x].email, temp[x].recovery.q1, temp[x].recovery.q2,
				temp[x].recovery.q3);
	}

	fclose(backupPtr);
	mModuleMain();
}

// staff menu for member info
void staffMenu() {
	int option;
	clearScreen();
	do {
		printf("STAFF MENU\n");
		printf("--------------------------------\n");
		printf("1. Search member\n");
		printf("2. display all member\n");
		printf("3. Member Activity Log\n");
		printf("4. Delete Account backup\n");
		printf("5. Exit\n");
		printf("--------------------------------\n");
		printf("Choose an option : ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 5) {
			rewind(stdin);
			option = 0;
		}

		switch (option) {
		case 1: searchMember(); break;
		case 2: displayAllMember(); break;
		case 3: memberActivityLog(); break;
		case 4: displayDeleted(); break;
		case 5: selectFunction(); break;
		default: printf("Invalid option..");
		}
	} while (option == 0);
}

// search member menu
void searchMember() {
	int option;
	clearScreen();
	do {
		printf("SEARCH MEMBER\n");
		printf("-------------------------\n");
		printf("1. Member ID\n");
		printf("2. Name\n");
		printf("3. age\n");
		printf("4. gender\n");
		printf("5. Back to Menu\n");
		printf("-------------------------\n");
		printf("Choose an option: ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 5) {
			rewind(stdin);
			option = 0;
		}

		switch (option) {
		case 1: searchID(); break;
		case 2: searchName(); break;
		case 3: searchAge(); break;
		case 4: searchGender(); break;
		case 5: staffMenu(); break;
		default: printf("Invalid option..\n");
		}
	} while (1);
}

void searchID() {
	clearScreen();
	MemberInfo temp[MAX_SIZE];
	FILE* searchFile;

	searchFile = fopen("member_detail.txt", "r");
	if (searchFile == NULL) {
		printf("Unable to open file...\n");
		exit(-1);
	}
	char memberID[20];
	int i = 0;
	int option;

	printf("Enter member ID : ");
	rewind(stdin);
	scanf("%s", &memberID);

	while (fscanf(searchFile, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp[i].memberID, temp[i].password, temp[i].name, &temp[i].age, &temp[i].gender,
		temp[i].ic, temp[i].phoneNo, temp[i].email, temp[i].recovery.q1, temp[i].recovery.q2, &temp[i].recovery.q3) != EOF) {
		if (strcmp(memberID, temp[i].memberID) == 0) {
			printf("MEMBER FOUND\n");
			printf("------------\n");
			printf("%-25s %-35s %-5s %-10s %-15s %-15s %-30s\n", "MEMBER ID", "NAME", "AGE", "GENDER", "IC", "PHONE NO.", "EMAIL");
			printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("%-25s %-35s %-5d %-10c %-15s %-15s %-30s\n", temp[i].memberID, temp[i].name, temp[i].age, temp[i].gender, temp[i].ic, temp[i].phoneNo, temp[i].email);
			printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			do {

				printf("1. Search another user?\n");
				printf("2. Back?\n");
				if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
					rewind(stdin);
					option = 0;
				}

				switch (option) {
				case 1: searchName(); break;
				case 2: searchMember(); break;
				default: printf("Invalid option...\n");
				}
			} while (option == 0);
		}
	}
	option = 0;
	printf("ID not found...\n");
	do {
		printf("----------------------------\n");
		printf("1. Try again?\n");
		printf("2. back to menu\n");
		printf("----------------------------\n");
		printf("choose an option: ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
			rewind(stdin);
			option = 0;
		}

		switch (option) {
		case 1: searchID(); break;
		case 2: searchMember(); break;
		default: printf("Invalid option..\n");
		}
	} while (1);
	fclose(searchFile);
}

void searchName() {
	clearScreen();
	MemberInfo temp[MAX_SIZE];
	FILE* searchFile;

	searchFile = fopen("member_detail.txt", "r");
	if (searchFile == NULL) {
		printf("Unable to open file...\n");
		exit(-1);
	}
	char memberName[30];
	int i = 0;
	int option;

	printf("Enter member Name : ");
	rewind(stdin);
	scanf("%[^\n]", &memberName);

	while (fscanf(searchFile, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp[i].memberID, temp[i].password, temp[i].name, &temp[i].age, &temp[i].gender,
		temp[i].ic, temp[i].phoneNo, temp[i].email, temp[i].recovery.q1, temp[i].recovery.q2, &temp[i].recovery.q3) != EOF) {
		if (strcmp(memberName, temp[i].name) == 0) {
			printf("MEMBER FOUND\n");
			printf("------------\n");
			printf("%-25s %-35s %-5s %-10s %-15s %-15s %-30s\n", "MEMBER ID", "NAME", "AGE", "GENDER", "IC", "PHONE NO.", "EMAIL");
			printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("%-25s %-35s %-5d %-10c %-15s %-15s %-30s\n", temp[i].memberID, temp[i].name, temp[i].age, temp[i].gender, temp[i].ic, temp[i].phoneNo, temp[i].email);
			printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			do {

				printf("1. Search another user?\n");
				printf("2. Back?\n");
				if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
					rewind(stdin);
					option = 0;
				}

				switch (option) {
				case 1: searchName(); break;
				case 2: searchMember(); break;
				default: printf("Invalid option...\n");
				}
			} while (option == 0);
		}
	}
	option = 0;
	printf("ID not found...\n");
	do {
		printf("----------------------------\n");
		printf("1. Try again?\n");
		printf("2. back to menu\n");
		printf("----------------------------\n");
		printf("choose an option: ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
			rewind(stdin);
			option = 0;
		}

		switch (option) {
		case 1: searchName(); break;
		case 2: searchMember(); break;
		default: printf("Invalid option..\n");
		}
	} while (1);
	fclose(searchFile);
}

void searchAge() {
	clearScreen();
	MemberInfo temp[MAX_SIZE];
	FILE* searchFile;

	searchFile = fopen("member_detail.txt", "r");
	if (searchFile == NULL) {
		printf("Unable to open file...\n");
		exit(-1);
	}
	int age;
	int i = 0;
	int option;
	int valid;

	printf("Enter Age : ");
	rewind(stdin);
	scanf("%d", &age);

	printf("MEMBER FOUND\n");
	printf("------------\n");
	printf("%-25s %-35s %-5s %-10s %-15s %-15s %-30s\n", "MEMBER ID", "NAME", "AGE", "GENDER", "IC", "PHONE NO.", "EMAIL");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	while (fscanf(searchFile, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp[i].memberID, temp[i].password, temp[i].name, &temp[i].age, &temp[i].gender,
		temp[i].ic, temp[i].phoneNo, temp[i].email, temp[i].recovery.q1, temp[i].recovery.q2, &temp[i].recovery.q3) != EOF) {
		if (age == temp[i].age) {
			printf("%-25s %-35s %-5d %-10c %-15s %-15s %-30s\n", temp[i].memberID, temp[i].name, temp[i].age, temp[i].gender, temp[i].ic, temp[i].phoneNo, temp[i].email);
			valid = 0;
		}
	}
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	do {
		printf("1. Search another user?\n");
		printf("2. Back?\n");
		if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
			rewind(stdin);
			option = 0;
		}

		switch (option) {
		case 1: searchAge(); break;
		case 2: searchMember(); break;
		default: printf("Invalid option...\n");
		}
	} while (option == 0);

	if (valid == 0) {
		option = 0;
		printf("no member found with that age...\n");
		do {
			printf("----------------------------\n");
			printf("1. Try again?\n");
			printf("2. back to menu\n");
			printf("----------------------------\n");
			printf("choose an option: ");
			if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
				rewind(stdin);
				option = 0;
			}

			switch (option) {
			case 1: searchID(); break;
			case 2: searchMember(); break;
			default: printf("Invalid option..\n");
			}
		} while (1);
	}
	fclose(searchFile);
}

void searchGender() {
	clearScreen();
	MemberInfo temp[MAX_SIZE];
	FILE* searchFile;

	searchFile = fopen("member_detail.txt", "r");
	if (searchFile == NULL) {
		printf("Unable to open file...\n");
		exit(-1);
	}
	char gender;
	int i = 0;
	int option;
	int valid;

	do {
		rewind(stdin);
		printf("Enter Gender (M = Male | F = Female): ");
		scanf("%c", &gender);
		printf("\n");

		// Try again if input is not M or F
		gender = toupper(gender);
		if (gender != 'M' && gender != 'F') {
			printf("Invalid Input. Please try again. M for male, F for female\n");
		}
	} while (gender != 'M' && gender != 'F');

	printf("MEMBER FOUND\n");
	printf("------------\n");
	printf("%-25s %-35s %-5s %-10s %-15s %-15s %-30s\n", "MEMBER ID", "NAME", "AGE", "GENDER", "IC", "PHONE NO.", "EMAIL");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	while (fscanf(searchFile, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp[i].memberID, temp[i].password, temp[i].name, &temp[i].age, &temp[i].gender,
		temp[i].ic, temp[i].phoneNo, temp[i].email, temp[i].recovery.q1, temp[i].recovery.q2, &temp[i].recovery.q3) != EOF) {
		if (gender == temp[i].gender) {
			printf("%-25s %-35s %-5d %-10c %-15s %-15s %-30s\n", temp[i].memberID, temp[i].name, temp[i].age, temp[i].gender, temp[i].ic, temp[i].phoneNo, temp[i].email);
			valid = 0;
		}
	}
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	do {

		printf("1. Search againr?\n");
		printf("2. Back?\n");
		if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
			rewind(stdin);
			option = 0;
		}

		switch (option) {
		case 1: searchGender(); break;
		case 2: searchMember(); break;
		default: printf("Invalid option...\n");
		}
	} while (option == 0);

	if (valid == 0) {
		option = 0;
		printf("ID not found...\n");
		do {
			printf("----------------------------\n");
			printf("1. Try again?\n");
			printf("2. back to menu\n");
			printf("----------------------------\n");
			printf("choose an option: ");
			if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
				rewind(stdin);
				option = 0;
			}

			switch (option) {
			case 1: searchName(); break;
			case 2: searchMember(); break;
			default: printf("Invalid option..\n");
			}
		} while (1);
	}
	fclose(searchFile);
}

// display all member in text file
void displayAllMember() {
	clearScreen();
	FILE* displayAll;
	displayAll = fopen("member_detail.txt", "r");
	if (displayAll == NULL) {
		printf("Error while opening file..\n");
		exit(-1);
	}
	MemberInfo temp[MAX_SIZE];
	int i = 0;

	do {
		int option;
		clearScreen();
		printf("MEMBER DATABASE\n");
		printf("-------------------------------\n");
		printf("1. Display all member\n");
		printf("2. Return to menu\n");
		printf("-------------------------------\n");
		printf("Choose an option: ");
		if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
			rewind(stdin);
			option = 0;
		}

		switch (option) {
		case 1:
			clearScreen();
			printf("MEMBER LIST\n");
			rintf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("%-25s %-35s %-5s %-10s %-15s %-15s %-30s\n", "MEMBER ID", "NAME", "AGE", "GENDER", "IC", "PHONE NO.", "EMAIL");
			printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			while (fscanf(displayAll, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp[i].memberID, temp[i].password, temp[i].name, &temp[i].age, &temp[i].gender,
				temp[i].ic, temp[i].phoneNo, temp[i].email, temp[i].recovery.q1, temp[i].recovery.q2, &temp[i].recovery.q3) != EOF) {
				printf("%-25s %-35s %-5d %-10c %-15s %-15s %-30s\n", temp[i].memberID, temp[i].name, temp[i].age, temp[i].gender, temp[i].ic, temp[i].phoneNo, temp[i].email);
			}
			printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			system("pause");
			staffMenu();
			break;

		case 2: staffMenu(); break;
		default: printf("Invalid Option..\n");
		}
	} while (1);

	fclose(displayAll);
}

// check member activity (Login/Signup
void memberActivityLog() {
	clearScreen();
	struct Activity {
		char id[21];
		int day, month, year;
		int hour, minute, second;
		char type[11];
	};
	struct Activity read;
	int count = 0;

	FILE* activity;
	activity = fopen("member_activity.txt", "r");
	if (activity == NULL) {
		printf("Error while opening file..\n");
		exit(-1);
	}


	printf("MEMBER ACTIVITY LOG\n");
	printf("-----------------------------------------------------\n");
	printf("%-25s %-10s %-8s %s\n", "Member ID", "Date", "Time", "Type");
	printf("-----------------------------------------------------\n");
	while (fscanf(activity, "%[^|]|%d/%d/%d %d:%d:%d|%s\n", &read.id, &read.day, &read.month, &read.year, &read.hour, &read.minute, &read.second, &read.type) != EOF) {
		printf("%-25s %02d/%02d/%-04d %02d:%02d:%02d %s\n", read.id, read.day, read.month, read.year, read.hour, read.minute, read.second, read.type);
		count++;
	}
	printf("-----------------------------------------------------\n");
	printf("Total of %d record has been found...\n", count);
	printf("Back To Menu\n");
	system("pause");
	staffMenu();

	fclose(activity);
}

// check delete account data
void displayDeleted() {
	clearScreen();
	FILE* deleted;
	deleted = fopen("deleted_backup.txt", "r");
	if (deleted == NULL) {
		printf("Error while opening file..\n");
		exit(-1);
	}
	MemberInfo temp;
	int count = 0;

	printf("DELETED MEMBER LOG\n");
	printf("%-25s %-35s %-5s %-10s %-15s %-15s %-30s\n", "MEMBER ID", "NAME", "AGE", "GENDER", "IC", "PHONE NO.", "EMAIL");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	while (fscanf(deleted, "%[^|]|%[^|]|%[^|]|%d|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s\n", temp.memberID, temp.password, temp.name, &temp.age, &temp.gender,
		temp.ic, temp.phoneNo, temp.email, temp.recovery.q1, temp.recovery.q2, &temp.recovery.q3) != EOF) {
		printf("%-25s %-35s %-5d %-10c %-15s %-15s %-30s\n", temp.memberID, temp.name, temp.age, temp.gender, temp.ic, temp.phoneNo, temp.email);
		count++;
	}
	if (count == 0) {
		printf("No record found\n");
	}
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Total of %d deleted record has been found...\n", count);
	printf("Back to menu\n");
	system("pause");

	fclose(deleted);
	staffMenu();
}


//train Scheduling module
void addTrain() {
	int checkId = -1;
	char cont;
	int checkTrainType = -1;

	system("cls");
	printf("=======================\n");
	printf("      Add Train   \n");
	printf("=======================\n");

	FILE* add;

	TrainScheduling addTrains, checkTrain;

	add = fopen("train.txt", "r");

	if (add == NULL) {
		printf("Error while opening the file\n");
		exit(-1);
	}

	do {
		do {
			printf("Enter train id (TXXX) : ");
			rewind(stdin);
			scanf("%s", &addTrains.trainId);

			int length = strlen(addTrains.trainId);
			int j = 0;

			while (j < length) {
				addTrains.trainId[j] = toupper(addTrains.trainId[j]);
				j++;
			}

			rewind(add);
			checkId = 1;

			while (fscanf(add, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
				&checkTrain.trainId, &checkTrain.trainType, &checkTrain.departureStation, &checkTrain.arrivalStation, &checkTrain.departureDate.day,
				&checkTrain.departureDate.month, &checkTrain.departureDate.year, &checkTrain.departureTime, &checkTrain.arrivalTime,
				&checkTrain.availableSeat, &checkTrain.price) != EOF) {
				if (strcmp(addTrains.trainId, checkTrain.trainId) == 0) {
					printf("\nRepeated Train ID Found\n\n");
					checkId = 0;
					break;
				}
			}
		} while (checkId == 0);

		do {
			checkTrainType = 1;
			printf("Enter train type (GOLD/SILVER/BRONZE) : ");
			rewind(stdin);
			scanf("%s", &addTrains.trainType);
			int length = strlen(addTrains.trainType);
			int j = 0;

			while (j < length) {
				addTrains.trainType[j] = toupper(addTrains.trainType[j]);
				j++;
			}

			if (strcmp(addTrains.trainType, "GOLD") != 0 && strcmp(addTrains.trainType, "SILVER") != 0 && strcmp(addTrains.trainType, "BRONZE") != 0) {
				printf("\nInvalid train type. Please choose between gold/silver/bronze.\n\n");
			}
			else {
				checkTrainType = 0;
			}
		} while (checkTrainType != 0);

		printf("Enter departure station : ");
		rewind(stdin);
		scanf("%[^\n]", &addTrains.departureStation);

		int checkArrival = 1;
		do {
			printf("Enter arrival station : ");
			rewind(stdin);
			scanf("%[^\n]", &addTrains.arrivalStation);

			if (strcmp(addTrains.arrivalStation, addTrains.departureStation) == 0) {
				printf("\nArrival Station cannot be same as the departure station\n\n");
			}
			else {
				checkArrival = 0;
			}
		} while (checkArrival != 0);

		int checkDate = 1;
		char input[12];
		do {
			printf("Enter departure date (DD/MM/YYYY) : ");
			rewind(stdin);
			scanf("%s", &input);

			if (sscanf(input, "%2d/%2d/%d", &addTrains.departureDate.day, &addTrains.departureDate.month, &addTrains.departureDate.year) != 3) {
				printf("\nInvalid input format. Please enter the date in the format DD/MM/YYYY.\n");
			}
			else if (addTrains.departureDate.year > 9999 || addTrains.departureDate.year < 2024) {
				printf("\nInvalid year.\n");
			}
			else if ((addTrains.departureDate.month == 4 || addTrains.departureDate.month == 6 || addTrains.departureDate.month == 9 || addTrains.departureDate.month == 11) && addTrains.departureDate.day > 30) {
				printf("\nInvalid day for this month. Please enter a day between 1 and 30.\n");
			}
			else if ((addTrains.departureDate.month == 1 || addTrains.departureDate.month == 3 || addTrains.departureDate.month == 5 || addTrains.departureDate.month == 7 ||
				addTrains.departureDate.month == 8 || addTrains.departureDate.month == 10 || addTrains.departureDate.month == 12) && addTrains.departureDate.day > 31) {
				printf("\nInvalid day for this month. Please enter a day between 1 and 31.\n");
			}
			else if (addTrains.departureDate.month == 2 && ((addTrains.departureDate.year % 4 == 0 && addTrains.departureDate.year % 100 != 0) || addTrains.departureDate.year % 400 == 0) && addTrains.departureDate.day > 29) {
				printf("\nInvalid day for February in a leap year. Please enter a day between 1 and 29.\n");
			}
			else if (addTrains.departureDate.month == 2 && ((addTrains.departureDate.year % 4 != 0 && addTrains.departureDate.year % 100 == 0) || addTrains.departureDate.year % 400 != 0) && addTrains.departureDate.day > 28) {
				printf("\nInvalid day for February in a non-leap year. Please enter a day between 1 and 28.\n");
			}
			else {
				checkDate = 0;
			}
		} while (checkDate != 0);


		int checkDepartureTime = 1;
		do {
			printf("Enter departure time (HHMM) : ");
			rewind(stdin);
			scanf("%d", &addTrains.departureTime);

			if (addTrains.departureTime >= 2400 || addTrains.departureTime < 0) {
				printf("\nInvalid Time. Please enter a time between 0000 and 2359\n\n");
			}
			else {
				checkDepartureTime = 0;
			}
		} while (checkDepartureTime != 0);

		int checkArrivalTime = 1;
		do {
			printf("Enter arrival time (HHMM) : ");
			rewind(stdin);
			scanf("%d", &addTrains.arrivalTime);

			if (addTrains.arrivalTime == addTrains.departureTime) {
				printf("\nArrival Time cannot be same as the departure time\n\n");
			}
			else if (addTrains.arrivalTime >= 2400 || addTrains.arrivalTime < 0) {
				printf("\nInvalid Time. Please enter a time between 0000 and 2359\n\n");
			}
			else {
				checkArrivalTime = 0;
			}
		} while (checkArrivalTime != 0);

		int checkSeat = 0;

		do {
			printf("Enter available seat (1 - 100): ");
			rewind(stdin);
			scanf("%d", &addTrains.availableSeat);

			checkSeat = addTrains.availableSeat;

			if (checkSeat > 100 || checkSeat <= 0) {
				printf("\nOut of bounds. Please enter within 1- 100.\n\n");
			}
		} while (checkSeat > 100 || checkSeat <= 0);

		printf("Enter price : ");
		rewind(stdin);
		scanf("%lf", &addTrains.price);

		fclose(add);

		add = fopen("train.txt", "a");

		if (add == NULL) {
			printf("Error while opening the file\n");
			exit(-1);
		}

		fprintf(add, "%s|%s|%s|%s|%d/%d/%d|%d|%d|%d|%.2lf\n", addTrains.trainId, addTrains.trainType, addTrains.departureStation, addTrains.arrivalStation, addTrains.departureDate.day, addTrains.departureDate.month, addTrains.departureDate.year, addTrains.departureTime, addTrains.arrivalTime, addTrains.availableSeat, addTrains.price);
		fclose(add);
		printf("\nAdded successfully\n");

		do {
			printf("\nDo you want to continue (Y = yes / N = no) ? : ");
			rewind(stdin);
			scanf("%c", &cont);

			cont = toupper(cont);

			if (cont == 'Y') {
				system("pause");
				addTrain();
			}
			else if (cont == 'N') {
				system("pause");
				system("cls");
				scheduleMain();
			}
			else {
				printf("\nInvalid choice.\n");
			}
		} while (cont != 'Y' && cont != 'N');
	} while (cont == 'Y');
}

void searchTrain() {
	char temp[5];
	char cont;

	system("cls");
	printf("=======================\n");
	printf("      Search Train   \n");
	printf("=======================\n");

	FILE* search;

	TrainScheduling searchTrains;

	search = fopen("train.txt", "r");

	if (search == NULL) {
		printf("Error while opening the file\n");
		exit(-1);
	}

	do {
		printf("\nEnter Train ID: ");
		rewind(stdin);
		scanf("%s", &temp);

		temp[0] = toupper(temp[0]);

		int found = 0;

		rewind(search);
		while (fscanf(search, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
			&searchTrains.trainId, &searchTrains.trainType, &searchTrains.departureStation, &searchTrains.arrivalStation, &searchTrains.departureDate.day,
			&searchTrains.departureDate.month, &searchTrains.departureDate.year, &searchTrains.departureTime, &searchTrains.arrivalTime,
			&searchTrains.availableSeat, &searchTrains.price) != EOF) {

			if (strcmp(temp, searchTrains.trainId) == 0) {
				printf("\nTrain ID: %s\n", searchTrains.trainId);
				printf("Train Type: %s\n", searchTrains.trainType);
				printf("Departure Station: %s\n", searchTrains.departureStation);
				printf("Arrival Station: %s\n", searchTrains.arrivalStation);
				printf("Departure Date: %02d/%02d/%d\n", searchTrains.departureDate.day, searchTrains.departureDate.month, searchTrains.departureDate.year);
				printf("Departure Time: %04d\n", searchTrains.departureTime);
				printf("Arrival Time: %04d\n", searchTrains.arrivalTime);
				printf("Available Seats: %d\n", searchTrains.availableSeat);
				printf("Price: %.2lf\n", searchTrains.price);

				found = 1;
			}
		}

		if (found == 0) {
			printf("\nTrain ID not found.\n");
		}

		fclose(search);

		do {
			printf("\nDo you want to continue searching (Y = yes / N = no) ? : ");
			rewind(stdin);
			scanf("%c", &cont);

			cont = toupper(cont);
			if (cont == 'Y') {
				system("pause");
				searchTrain();
			}
			else if (cont == 'N') {
				system("pause");
				system("cls");
				scheduleMain();
			}
			else {
				printf("\nInvalid choice... Please choose between Y and N.\n");
			}
		} while (cont != 'Y' && cont != 'N');
	} while (cont == 'Y');
}

void display() {
	FILE* display;

	TrainScheduling displayTrain;

	display = fopen("train.txt", "r");

	if (display == NULL) {
		printf("Error while opening the file.\n");
		exit(-1);
	}

	printf("======================================================================================================================================\n");
	printf("Train ID | Train Type | Departure Station | Arrival Station | Departure Date | Departure Time | Arrival Time | Available Seat | Price\n");
	printf("======================================================================================================================================\n");

	while (fscanf(display, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
		&displayTrain.trainId, &displayTrain.trainType, &displayTrain.departureStation, &displayTrain.arrivalStation, &displayTrain.departureDate.day,
		&displayTrain.departureDate.month, &displayTrain.departureDate.year, &displayTrain.departureTime, &displayTrain.arrivalTime,
		&displayTrain.availableSeat, &displayTrain.price) != EOF) {
		printf("%-10s %-12s %-19s %-17s   %02d/%02d/%d         %04d             %04d             %3d         %.2lf\n",
			displayTrain.trainId, displayTrain.trainType, displayTrain.departureStation, displayTrain.arrivalStation, displayTrain.departureDate.day,
			displayTrain.departureDate.month, displayTrain.departureDate.year, displayTrain.departureTime, displayTrain.arrivalTime,
			displayTrain.availableSeat, displayTrain.price);
	}

	fclose(display);
}

void modifyTrain() {
	system("cls");
	printf("=======================\n");
	printf("     Modify Train      \n");
	printf("=======================\n");

	FILE* read;
	FILE* modify;

	TrainScheduling modifyTrains[100];

	int i = 0;
	int newDepartureTime = 0, newArrivalTime = 0, newDay = 0, newMonth = 0, newYear = 0, newAvailableSeat = 0, choice = 0;
	char input[5], cont, conts, confirmModify;

	display();

	read = fopen("train.txt", "r");

	if (read == NULL) {
		printf("Error while opening the file.\n");
		exit(-1);
	}

	do {
		printf("\nEnter Train Id : ");
		rewind(stdin);
		scanf("%s", &input);

		input[0] = toupper(input[0]);

		while (fscanf(read, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
			&modifyTrains[i].trainId, &modifyTrains[i].trainType, &modifyTrains[i].departureStation, &modifyTrains[i].arrivalStation, &modifyTrains[i].departureDate.day,
			&modifyTrains[i].departureDate.month, &modifyTrains[i].departureDate.year, &modifyTrains[i].departureTime, &modifyTrains[i].arrivalTime,
			&modifyTrains[i].availableSeat, &modifyTrains[i].price) != EOF) {
			if (strcmp(modifyTrains[i].trainId, input) == 0) {
				printf("\nAre you sure to modify (Y = yes) ? : ");
				rewind(stdin);
				scanf("%c", &confirmModify);

				if (toupper(confirmModify) == 'Y') {
					printf("\n1. Departure Date\n");
					printf("2. Departure Time\n");
					printf("3. Arrival Time\n");
					printf("4. Available Seat\n");
					printf("Please choose a content to modify : ");
					rewind(stdin);
					scanf("%d", &choice);

					switch (choice) {
					case 1:
						printf("\nEnter new departure date (DD/MM/YYYY) : ");
						rewind(stdin);
						scanf("%d/%d/%d", &newDay, &newMonth, &newYear);

						modifyTrains[i].departureDate.day = newDay;
						modifyTrains[i].departureDate.month = newMonth;
						modifyTrains[i].departureDate.year = newYear;

						printf("\nModified successfully.\n");
						break;
					case 2:
						printf("\nEnter new departure time (HHMM) : ");
						rewind(stdin);
						scanf("%d", &newDepartureTime);

						modifyTrains[i].departureTime = newDepartureTime;

						printf("\nModified successfully.\n");
						break;
					case 3:
						printf("\nEnter new arrival time (HHMM) : ");
						rewind(stdin);
						scanf("%d", &newArrivalTime);

						modifyTrains[i].arrivalTime = newArrivalTime;

						printf("\nModified successfully.\n");
						break;
					case 4:
						printf("\nEnter new available seat (1 - 100) : ");
						rewind(stdin);
						scanf("%d", &newAvailableSeat);

						modifyTrains[i].availableSeat = newAvailableSeat;

						printf("\nModified successfully.\n");
						break;
					}
				}
			}
			i++;
		}

		fclose(read);

		modify = fopen("train.txt", "w");

		if (modify == NULL) {
			printf("Error while opening the file.\n");
			exit(-1);
		}

		for (int y = 0; y < i; y++) {
			fprintf(modify, "%s|%s|%s|%s|%d/%d/%d|%d|%d|%d|%.2lf\n", modifyTrains[y].trainId, modifyTrains[y].trainType, modifyTrains[y].departureStation,
				modifyTrains[y].arrivalStation, modifyTrains[y].departureDate.day, modifyTrains[y].departureDate.month, modifyTrains[y].departureDate.year,
				modifyTrains[y].departureTime, modifyTrains[y].arrivalTime, modifyTrains[y].availableSeat, modifyTrains[y].price);
		}

		fclose(modify);

		do {
			printf("\nDo you want to continue modify (Y = yes / N = no) ? ");
			rewind(stdin);
			scanf("%c", &conts);

			conts = toupper(conts);
			if (conts == 'Y') {
				system("pause");
				modifyTrain();
			}
			else if (conts == 'N') {
				system("pause");
				system("cls");
				scheduleMain();
			}
			else {
				printf("\nInvalid choice... Please choose between Y and N.\n");
			}
		} while (conts != 'Y' && conts != 'N');
	} while (conts == 'Y');
}

void displayTrain() {
	char choice;
	system("cls");
	printf("=======================\n");
	printf("     Display Train     \n");
	printf("=======================\n");

	FILE* display;

	TrainScheduling displayTrains;

	display = fopen("train.txt", "r");

	if (display == NULL) {
		printf("Error while opening the file.\n");
		exit(-1);
	}

	printf("=======================================================================================================================================\n");
	printf("Train ID | Train Type | Departure Station | Arrival Station | Departure Date | Departure Time | Arrival Time | Available Seat | Price\n");
	printf("=======================================================================================================================================\n");

	while (fscanf(display, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
		&displayTrains.trainId, &displayTrains.trainType, &displayTrains.departureStation, &displayTrains.arrivalStation, &displayTrains.departureDate.day,
		&displayTrains.departureDate.month, &displayTrains.departureDate.year, &displayTrains.departureTime, &displayTrains.arrivalTime,
		&displayTrains.availableSeat, &displayTrains.price) != EOF) {
		printf("%-10s %-12s %-19s %-17s   %02d/%02d/%d         %04d             %04d             %3d         %.2lf\n",
			displayTrains.trainId, displayTrains.trainType, displayTrains.departureStation, displayTrains.arrivalStation, displayTrains.departureDate.day,
			displayTrains.departureDate.month, displayTrains.departureDate.year, displayTrains.departureTime, displayTrains.arrivalTime,
			displayTrains.availableSeat, displayTrains.price);
	}

	fclose(display);

	do {
		printf("\nDo you want to continue (Y = yes / N = No) ? ");
		rewind(stdin);
		scanf("%c", &choice);

		if (toupper(choice) == 'Y') {
			printf("\nWhy do you want to see the same thing again...\n");
			printf("Access denied.\n");
		}
		else if (toupper(choice) == 'N') {
			system("pause");
			system("cls");
			scheduleMain();
		}
		else {
			printf("\nInvalid choice\n");
		}
	} while (choice != 'N');
}

void deleteTrain() {
	system("cls");
	printf("=======================\n");
	printf("      Delete Train     \n");
	printf("=======================\n");

	FILE* read, * delete;
	TrainScheduling deleteTrains[100];
	int i = 0, found = 0, record = -1;
	char input[5], cont, confirmDelete, conts;

	display();

	read = fopen("train.txt", "r");
	if (read == NULL) {
		printf("Error while opening the file.\n");
		exit(-1);
	}

	while (fscanf(read, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
		&deleteTrains[i].trainId, &deleteTrains[i].trainType, &deleteTrains[i].departureStation, &deleteTrains[i].arrivalStation,
		&deleteTrains[i].departureDate.day, &deleteTrains[i].departureDate.month, &deleteTrains[i].departureDate.year,
		&deleteTrains[i].departureTime, &deleteTrains[i].arrivalTime, &deleteTrains[i].availableSeat, &deleteTrains[i].price) != EOF) {
		i++;
	}
	fclose(read);

	do {
		printf("Enter Train Id : ");
		rewind(stdin);
		scanf("%s", &input);
		input[0] = toupper(input[0]);

		for (int j = 0; j < i; j++) {
			if (strcmp(deleteTrains[j].trainId, input) == 0) {
				printf("\nAre you sure to delete (Y = yes) ? : ");
				rewind(stdin);
				scanf(" %c", &confirmDelete);
				confirmDelete = toupper(confirmDelete);
				if (confirmDelete == 'Y') {
					record = j;
					found = 1;
					printf("\nDeleted Successfully.\n");
					break;
				}
				else {
					found = -1;
					break;
				}
			}
		}

		if (found == 0) {
			printf("\nTrain ID not found.\n");
		}
		else if (found == -1) {
			printf("\nDenial of confirmation.\n");
		}
		else {
			for (int k = record; k < i - 1; k++) {
				deleteTrains[k] = deleteTrains[k + 1];
			}
			i--;
		}

		delete = fopen("train.txt", "w");
		if (delete == NULL) {
			printf("Error while opening the file.\n");
			exit(-1);
		}

		for (int m = 0; m < i; m++) {
			fprintf(delete, "%s|%s|%s|%s|%d/%d/%d|%d|%d|%d|%.2lf\n", deleteTrains[m].trainId, deleteTrains[m].trainType, deleteTrains[m].departureStation,
				deleteTrains[m].arrivalStation, deleteTrains[m].departureDate.day, deleteTrains[m].departureDate.month, deleteTrains[m].departureDate.year,
				deleteTrains[m].departureTime, deleteTrains[m].arrivalTime, deleteTrains[m].availableSeat, deleteTrains[m].price);
		}

		fclose(delete);

		printf("\nDo your want to continue deleting (Y = yes / N = no) ? : ");
		rewind(stdin);
		scanf(" %c", &conts);
		conts = toupper(conts);

		if (conts == 'Y') {
			system("pause");
			deleteTrain();
		}
		else if (conts == 'N') {
			system("pause");
			system("cls");
			scheduleMain();
		}
		else {
			printf("\nInvalid choice... Please choose between Y and N.\n");
		}
	} while (conts == 'Y');
}

void reportTrain() {
	char cont;
	char select;
	int sto = 0;

	FILE* report;

	TrainScheduling reportTrains[100];

	report = fopen("train.txt", "r");

	if (report == NULL) {
		printf("Error while opening the file.\n");
		exit(-1);
	}


	int chooseSession = 0;
	do {
		system("cls");
		printf("=======================\n");
		printf("      Report Train     \n");
		printf("=======================\n");
		printf("1. Morning Peak Hour\n");
		printf("2. Evening Peak Hour\n");
		printf("3. Return main page\n");
		printf("Please choose one session : ");
		rewind(stdin);
		scanf("%d", &chooseSession);

		system("pause");
		system("cls");

		if (chooseSession == 1) {
			printf("========================\n");
			printf("     THRESHOLD SEAT     \n");
			printf("========================\n");
			printf("======================================================================================================================================\n");
			printf("Train ID | Train Type | Departure Station | Arrival Station | Departure Date | Departure Time | Arrival Time | Available Seat | Price\n");
			printf("======================================================================================================================================\n");

			int i = 0;

			while (fscanf(report, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
				&reportTrains[i].trainId, &reportTrains[i].trainType, &reportTrains[i].departureStation, &reportTrains[i].arrivalStation, &reportTrains[i].departureDate.day,
				&reportTrains[i].departureDate.month, &reportTrains[i].departureDate.year, &reportTrains[i].departureTime, &reportTrains[i].arrivalTime,
				&reportTrains[i].availableSeat, &reportTrains[i].price) != EOF) {

				if (morningPeakHour(reportTrains[i].departureTime)) {
					if (reportTrains[i].availableSeat > 50) {
						printf("%-10s %-12s %-19s %-17s   %02d/%02d/%d         %04d             %04d             %3d         %.2lf\n",
							reportTrains[i].trainId, reportTrains[i].trainType, reportTrains[i].departureStation, reportTrains[i].arrivalStation, reportTrains[i].departureDate.day,
							reportTrains[i].departureDate.month, reportTrains[i].departureDate.year, reportTrains[i].departureTime, reportTrains[i].arrivalTime,
							reportTrains[i].availableSeat, reportTrains[i].price);

					}
					i++;
				}
			}

			printf("\nOn top listed trains are suggested to move coaches to below listed pack train.\n\n");

			printf("======================================================================================================================================\n");
			printf("Train ID | Train Type | Departure Station | Arrival Station | Departure Date | Departure Time | Arrival Time | Available Seat | Price\n");
			printf("======================================================================================================================================\n");

			int j = 0;
			rewind(report);
			while (fscanf(report, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
				&reportTrains[j].trainId, &reportTrains[j].trainType, &reportTrains[j].departureStation, &reportTrains[j].arrivalStation, &reportTrains[j].departureDate.day,
				&reportTrains[j].departureDate.month, &reportTrains[j].departureDate.year, &reportTrains[j].departureTime, &reportTrains[j].arrivalTime,
				&reportTrains[j].availableSeat, &reportTrains[j].price) != EOF) {
				if (morningPeakHour(reportTrains[j].departureTime)) {
					if (reportTrains[j].availableSeat < 50) {
						printf("%-10s %-12s %-19s %-17s   %02d/%02d/%d         %04d             %04d             %3d         %.2lf\n",
							reportTrains[j].trainId, reportTrains[j].trainType, reportTrains[j].departureStation, reportTrains[j].arrivalStation, reportTrains[j].departureDate.day,
							reportTrains[j].departureDate.month, reportTrains[j].departureDate.year, reportTrains[j].departureTime, reportTrains[j].arrivalTime,
							reportTrains[j].availableSeat, reportTrains[j].price);
					}
					j++;
				}
			}

			do {
				printf("\nReturn to previous page ? (Y = yes / N = no) : ");
				rewind(stdin);
				scanf("%c", &select);

				if (toupper(select) == 'Y') {
					system("pause");
					system("cls");
					reportTrain();
				}
				else if (toupper(select) == 'N') {
					printf("\nWhy do you want to see the same report again?\n");
					printf("Access Denied.\n");
				}
				else {
					printf("\nInvalid choice\n");
				}
			} while (select != 'Y');
		}
		else if (chooseSession == 2) {
			printf("========================\n");
			printf("     THRESHOLD SEAT     \n");
			printf("========================\n");
			printf("======================================================================================================================================\n");
			printf("Train ID | Train Type | Departure Station | Arrival Station | Departure Date | Departure Time | Arrival Time | Available Seat | Price\n");
			printf("======================================================================================================================================\n");

			int i = 0;

			while (fscanf(report, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
				&reportTrains[i].trainId, &reportTrains[i].trainType, &reportTrains[i].departureStation, &reportTrains[i].arrivalStation, &reportTrains[i].departureDate.day,
				&reportTrains[i].departureDate.month, &reportTrains[i].departureDate.year, &reportTrains[i].departureTime, &reportTrains[i].arrivalTime,
				&reportTrains[i].availableSeat, &reportTrains[i].price) != EOF) {

				if (eveningPeakHour(reportTrains[i].departureTime)) {
					if (reportTrains[i].availableSeat > 50) {
						printf("%-10s %-12s %-19s %-17s   %02d/%02d/%d         %04d             %04d             %3d         %.2lf\n",
							reportTrains[i].trainId, reportTrains[i].trainType, reportTrains[i].departureStation, reportTrains[i].arrivalStation, reportTrains[i].departureDate.day,
							reportTrains[i].departureDate.month, reportTrains[i].departureDate.year, reportTrains[i].departureTime, reportTrains[i].arrivalTime,
							reportTrains[i].availableSeat, reportTrains[i].price);

					}
					i++;
				}
			}

			printf("\nOn top listed trains are suggested to move coaches to below listed pack train.\n\n");

			printf("======================================================================================================================================\n");
			printf("Train ID | Train Type | Departure Station | Arrival Station | Departure Date | Departure Time | Arrival Time | Available Seat | Price\n");
			printf("======================================================================================================================================\n");

			int j = 0;
			rewind(report);
			while (fscanf(report, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
				&reportTrains[j].trainId, &reportTrains[j].trainType, &reportTrains[j].departureStation, &reportTrains[j].arrivalStation, &reportTrains[j].departureDate.day,
				&reportTrains[j].departureDate.month, &reportTrains[j].departureDate.year, &reportTrains[j].departureTime, &reportTrains[j].arrivalTime,
				&reportTrains[j].availableSeat, &reportTrains[j].price) != EOF) {
				if (eveningPeakHour(reportTrains[j].departureTime)) {
					if (reportTrains[j].availableSeat < 50) {
						printf("%-10s %-12s %-19s %-17s   %02d/%02d/%d         %04d             %04d             %3d         %.2lf\n",
							reportTrains[j].trainId, reportTrains[j].trainType, reportTrains[j].departureStation, reportTrains[j].arrivalStation, reportTrains[j].departureDate.day,
							reportTrains[j].departureDate.month, reportTrains[j].departureDate.year, reportTrains[j].departureTime, reportTrains[j].arrivalTime,
							reportTrains[j].availableSeat, reportTrains[j].price);
					}
					j++;
				}
			}

			do {
				printf("\nReturn to previous page ? (Y = yes / N = no) : ");
				rewind(stdin);
				scanf("%c", &select);

				if (toupper(select) == 'Y') {
					system("pause");
					system("cls");
					reportTrain();
				}
				else if (toupper(select) == 'N') {
					printf("\nWhy do you want to see the same report again?\n");
					printf("Access Denied.\n");
				}
				else {
					printf("\nInvalid choice\n");
				}
			} while (select != 'Y');
		}
		else if (chooseSession == 3) {
			reportMenu();
		}
	} while (chooseSession < 1 || chooseSession > 3);

	fclose(report);
}

int morningPeakHour(int time) {
	return (time >= MORNING_PEAK_HOUR_START && time <= MORNING_PEAK_HOUR_END);
}

int eveningPeakHour(int time) {
	return (time >= EVENING_PEAK_HOUR_START && time <= EVENING_PEAK_HOUR_END);
}

void scheduleMain() {
	int choice = 0;
	system("cls");
	do {
		printf("=======================\n");
		printf("Train Scheduling Module\n");
		printf("=======================\n");
		printf("1. Add Train   \n");
		printf("2. Search Train\n");
		printf("3. Modify Train\n");
		printf("4. Display Train\n");
		printf("5. Delete Train\n");
		printf("6. Exit\n");
		printf("Please choose a function (1-6) > ");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			addTrain();
			break;
		case 2:
			searchTrain();
			break;
		case 3:
			modifyTrain();
			break;
		case 4:
			displayTrain();
			break;
		case 5:
			deleteTrain();
			break;
		case 6:
			printf("\nBye Bye!\n");
			selectFunction();
			break;
		default:
			printf("\n\nInvalid choice! Please choose between 1 - 6\n\n");
		}
	} while (choice > 6);
}

// Train Booking Module
Date selectDate() {
	SYSTEMTIME t;
	GetLocalTime(&t);

	printf("========================\n");
	printf("\tTrip Date\n");
	printf("========================\n");
	Date date;

	do {
		printf("Please enter today's date to start selecting your trip (DD/MM/YYYY): ");
		rewind(stdin);
		scanf("%2d/%2d/%d", &date.day, &date.month, &date.year);

		// Check validation of day and month
		if (date.year < t.wYear ||
			(date.year == t.wYear && date.month < t.wMonth) ||
			(date.year == t.wYear && date.month == t.wMonth && date.day < t.wDay)) {
			printf("Please enter a future date.\n\n");
		}
		else if (date.month < 1 || date.month > 12) {
			printf("Invalid month. Please enter a month between 1 and 12.\n\n");
		}
		else if (date.day < 1 || date.day > 31) {
			printf("Invalid day. Please enter a day between 1 and 31.\n\n");
		}
		else if ((date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) && date.day > 30) {
			printf("Invalid day for this month. Please enter a day between 1 and 30.\n\n");
		}
		else if (date.month == 2 && ((date.year % 4 == 0 && date.year % 100 != 0) || date.year % 400 == 0) && date.day > 29) {
			printf("Invalid day for February in a leap year. Please enter a day between 1 and 29.\n\n");
		}
		else if (date.month == 2 && ((date.year % 4 != 0 || date.year % 100 == 0) && date.year % 400 != 0) && date.day > 28) {
			printf("Invalid day for February in a non-leap year. Please enter a day between 1 and 28.\n\n");
		}
		else {
			return date;
		}
	} while (1);
}

int noOfPax() {
	char choice;
	int pax;

	//insert number of pax for the trip
	printf("\nPlease enter no of pax for the trip: ");
	rewind(stdin);
	scanf("%d", &pax);

	do {
		//confirmation
		printf("Your trip is %d pax?\n", pax);
		printf("Yes'Y'/ No'N': ");
		rewind(stdin);
		scanf(" %c", &choice);
		choice = toupper(choice);

		switch (choice) {
		case'Y': return pax;
		case'N': return noOfPax();
		default: printf("Invalid Choice. Please enter again.\n\n"); break;
		}
	} while (choice != 'Y');
}

void selectPlace(char* depPlace) {
	Payment train;
	int found = 0;
	char choice;

	FILE* selPlace;

	do {
		selPlace = fopen("train.txt", "r");
		if (selPlace == NULL) {
			printf("Error opening file");
			system("pause");
			ticketBookingMenu();
			return;
		}

		//insert depart place that user prefer
		printf("\nPlease enter your depart place: ");
		rewind(stdin);
		scanf("%[^\n]", depPlace);

		printf("\n");
		printf("========================\n");
		printf("     Train Available\n");
		printf("========================\n");
		printf("%-10s %-13s %-15s %-15s %-12s %-12s %-12s %-15s %6s\n",
			"Train ID", "Train Type", "Departure", "Destination", "Depart Date", "Depart Time", "Return Time", "Seat Available", "Fare");
		printf("========   ==========    =========       ===========     ===========  ===========  ===========  ==============   =====\n");

		//while (fscanf(selPlace, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d:%d|%d:%d|%d|%lf\n")
		while (fscanf(selPlace, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
			&train.trainNo, &train.trainType, &train.departPlace, &train.destination,
			&train.trainInfo.dateDepAvailable.day, &train.trainInfo.dateDepAvailable.month, &train.trainInfo.dateDepAvailable.year,
			&train.trainInfo.timeDepAvailable, &train.trainInfo.timeDestAvailable, &train.trainInfo.seatStillAvailable, &train.trainInfo.fare) != EOF) {

			//compare the user input depart place with the depart place in the file
			if (strcmp(train.departPlace, depPlace) == 0) {
				//printf("%-10s %-13s %-15s %-15s %2d/%2d/%d %10d:%02d %9d:%02d %15d %7.2lf\n")
				printf("%-10s %-13s %-15s %-15s %2d/%2d/%d %11d %10d %15d %7.2lf\n",
					train.trainNo, train.trainType, train.departPlace, train.destination,
					train.trainInfo.dateDepAvailable.day, train.trainInfo.dateDepAvailable.month, train.trainInfo.dateDepAvailable.year,
					train.trainInfo.timeDepAvailable, train.trainInfo.timeDestAvailable, train.trainInfo.seatStillAvailable, train.trainInfo.fare);
				found++; //if compare successfully add found
			}
		}

		fclose(selPlace);

		if (found == 0) {
			printf("No trip found.\n\n");

			do {
				printf("\nDo you want to continue(Yes'Y'/ No'N')? ");
				rewind(stdin);
				scanf(" %c", &choice);
				choice = toupper(choice);

				if (choice != 'Y' && choice != 'N') {
					printf("Invalid choice\n\n");
				}
				else if (choice == 'N') {
					ticketBookingMenu();
				}
			} while (choice != 'Y' && choice != 'N');

		}
		else { break; }

	} while (strcmp(train.departPlace, depPlace) != 0 && choice == 'Y');

}

void selectTrain(char* trainno) {
	Payment train;
	FILE* selPlace;

	do {
		//insert train no
		printf("\nPlease enter Train No that you prefer (or enter '0' to cancel): ");
		rewind(stdin);
		scanf("%[^\n]", trainno);

		if (strcmp(trainno, "0") == 0) {
			printf("Booking canceled.\n");
			ticketBookingMenu();
		}

		selPlace = fopen("train.txt", "r");
		if (selPlace == NULL) {
			printf("Error opening file");
			return;
		}

		//while (fscanf(selPlace, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d:%d|%d:%d|%d|%lf\n",
		while (fscanf(selPlace, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
			&train.trainNo, &train.trainType, &train.departPlace, &train.destination,
			&train.trainInfo.dateDepAvailable.day, &train.trainInfo.dateDepAvailable.month, &train.trainInfo.dateDepAvailable.year,
			&train.trainInfo.timeDepAvailable, &train.trainInfo.timeDestAvailable, &train.trainInfo.seatStillAvailable, &train.trainInfo.fare) != EOF) {

			//compare user input's train no with the train no in the file
			if (strcmp(train.trainNo, trainno) == 0) {
				fclose(selPlace);
				return;
			}
		}

		if (strcmp(train.trainNo, trainno) != 0) {
			printf("Please enter a valid Train No or '0' to cancel.\n");
		}

	} while (strcmp(train.trainNo, trainno) != 0);
}

void selectPayment(char* paymentMethod) {
	do {
		printf("\nThe available payment methods are:\n");
		printf("Visa / TouchNGo / Online Banking\n\n");
		printf("Please enter your payment method: ");
		rewind(stdin);
		scanf("%[^\n]", paymentMethod);

		//check validation
		if ((strcmp(paymentMethod, "Visa") != 0) && (strcmp(paymentMethod, "TouchNGo") != 0) && (strcmp(paymentMethod, "Online Banking") != 0)) {
			printf("Invalid payment method. Please enter again!\n");
		}
	} while ((strcmp(paymentMethod, "Visa") != 0) && (strcmp(paymentMethod, "TouchNGo") != 0) && (strcmp(paymentMethod, "Online Banking") != 0));

	printf("Payment method selected: %s\n", paymentMethod);
}

void generateRandomReceiptID(char* receiptID, int length) {
	const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	const size_t charsetSize = sizeof(charset) - 1;

	do {
		for (int i = 0; i < length; ++i) {
			receiptID[i] = charset[rand() % charsetSize];
		}
		receiptID[length] = '\0'; // Null-terminate the string

		// Check if receiptID already exists
		FILE* file = fopen("receipt.bin", "rb");
		if (file != NULL) {
			Payment temp;
			while (fread(&temp, sizeof(Payment), 1, file) == 1) {
				if (strcmp(temp.receiptId, receiptID) == 0) {
					fclose(file);
					file = NULL;
					break;
				}
			}
			if (file != NULL) {
				fclose(file);
				break; // Exit loop if receiptID is unique
			}
		}
	} while (1);
}

void printReceipt(Payment receipt) {
	printf("Receipt Id     : %s\n", receipt.receiptId);
	printf("Train No       : %s\n", receipt.trainNo);
	printf("Date           : %02d/%02d/%d\n", receipt.ticketInfo.startDate.day, receipt.ticketInfo.startDate.month, receipt.ticketInfo.startDate.year);
	printf("Pax            : %d\n", receipt.ticketInfo.noPax);
	printf("Payment Method : %s\n", receipt.paymentMethod);
	printf("Amount         : RM%.2lf\n", receipt.paymentAmount);
}

void addBooking() {
	Payment train, receipt;
	char tripChoice, choice1, choice2;

	system("cls");
	//user input
	receipt.ticketInfo.startDate = selectDate();
	receipt.ticketInfo.noPax = noOfPax();
	selectPlace(receipt.departPlace);
	selectTrain(receipt.trainNo);
	selectPayment(receipt.paymentMethod);

	FILE* readNo = fopen("train.txt", "r");
	if (readNo == NULL) {
		printf("Error Opening File.\n");
		system("pause");
		ticketBookingMenu();
		return;
	}

	//while (fscanf(selPlace, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d:%d|%d:%d|%d|%lf\n",
	while (fscanf(readNo, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
		&train.trainNo, &train.trainType, &train.departPlace, &train.destination,
		&train.trainInfo.dateDepAvailable.day, &train.trainInfo.dateDepAvailable.month, &train.trainInfo.dateDepAvailable.year,
		&train.trainInfo.timeDepAvailable, &train.trainInfo.timeDestAvailable, &train.trainInfo.seatStillAvailable, &train.trainInfo.fare) != EOF) {

		if (strcmp(receipt.trainNo, train.trainNo) == 0) {
			printf("The fare of your trip: RM%.2lf\n", train.trainInfo.fare);
		}
	}

	fclose(readNo);

	//count for the amount 
	receipt.paymentAmount = receipt.ticketInfo.noPax * train.trainInfo.fare;

	FILE* ptr;
	ptr = fopen("receipt.bin", "ab"); // Append mode
	if (ptr == NULL) {
		printf("Error Opening File.\n");
		system("pause");
		ticketBookingMenu();
		return;
	}

	printf("\n========================\n");
	printf("      Trip Details\n");
	printf("========================\n");
	generateRandomReceiptID(receipt.receiptId, 8);
	printReceipt(receipt);

	do {
		//check validation
		printf("\nIs this the trip that you select?\n");
		printf("Yes'Y'/ No'N': ");
		rewind(stdin);
		scanf(" %c", &tripChoice);
		tripChoice = toupper(tripChoice);

		switch (tripChoice) {
		case 'Y':
			fwrite(&receipt, sizeof(Payment), 1, ptr);
			printf("\nDon't forget to copy/remember your receipt id.\n");
			printf("Booking confirmed and saved.\n");
			fclose(ptr);

			do {
				printf("\nDo you want to continue selecting trip?\n");
				printf("Yes'Y'/ No'N': ");
				rewind(stdin);
				scanf(" %c", &choice1);
				choice1 = toupper(choice1);

				switch (choice1) {
				case 'Y':
					system("pause");
					addBooking(); break;
				case 'N':
					system("pause");
					ticketBookingMenu(); break;
				default:
					printf("Invalid Choice. Please enter again.\n\n"); break;
				}
			} while (choice1 != 'Y');
			break;

		case 'N':
			fclose(ptr);
			do {
				printf("\nDo you want to continue selecting trip?\n");
				printf("Yes'Y'/ No'N': ");
				rewind(stdin);
				scanf(" %c", &choice2);
				choice2 = toupper(choice2);

				switch (choice2) {
				case 'Y':
					system("pause");
					addBooking(); break;
				case 'N':
					system("pause");
					ticketBookingMenu(); break;
				default:
					printf("Invalid Choice. Please enter again.\n\n"); break;
				}
			} while (choice2 != 'Y');
			break;

		default:
			fclose(ptr);
			printf("Invalid Choice. Please enter again.\n"); break;
		}
	} while (tripChoice != 'Y');
}

void displayBooking() {
	Payment receipt;
	char choice;
	char id[9];
	int found = 0;

	system("cls");
	printf("\n========================\n");
	printf("     Display Booking\n");
	printf("========================\n");
	printf("Please enter your Receipt Id: ");
	rewind(stdin);
	scanf(" %8s", id);

	FILE* ptr = fopen("receipt.bin", "rb");
	if (ptr == NULL) {
		printf("Error Opening File.\n");
		system("pause");
		ticketBookingMenu();
		return;
	}

	while (fread(&receipt, sizeof(Payment), 1, ptr) != 0) {
		if (strcmp(receipt.receiptId, id) == 0) {
			printf("\n========================\n");
			printf("        Receipt\n");
			printf("========================\n");
			printReceipt(receipt);
			found = 1;
			break;
		}
	}

	if (!found) {
		printf("No receipi Id found.\n");
	}

	fclose(ptr);

	do {
		printf("\nDo you want to continue?\n");
		printf("Yes'Y'/ No'N': ");
		rewind(stdin);
		scanf(" %c", &choice);
		choice = toupper(choice);

		switch (choice) {
		case 'Y':
			system("pause");
			ticketBookingMenu(); break;
		case 'N':
			exit(0); break;
		default:
			printf("Invalid Choice. Please enter again.\n\n"); break;
		}
	} while (choice != 'Y');
}

void modifyBooking() {
	Payment train, receipt[100], newReceipt;
	char receiptChoice, choice;
	char id[9];
	int i = 0, self = 0, j = 0;

	system("cls");
	printf("\n========================\n");
	printf("     Modify Booking\n");
	printf("========================\n");
	printf("Please enter your Receipt Id: ");
	rewind(stdin);
	scanf(" %8s", id);

	FILE* read = fopen("receipt.bin", "rb");
	if (read == NULL) {
		printf("Error Opening File.\n");
		system("pause");
		ticketBookingMenu();
		return;
	}

	while (fread(&receipt[i], sizeof(Payment), 1, read) != 0) {
		if (strcmp(receipt[i].receiptId, id) == 0) {
			printf("\n========================\n");
			printf("        Receipt\n");
			printf("========================\n");
			printReceipt(receipt[i]);
			self = i;
		}
		i++;
	}
	fclose(read);

	do {
		//check validation
		printf("\nIs this your receipt?\n");
		printf("Yes'Y'/ No'N': ");
		rewind(stdin);
		scanf(" %c", &receiptChoice);
		receiptChoice = toupper(receiptChoice);

		switch (receiptChoice) {
		case 'Y':
			//rewrite the booking
			printf("\n========================\n");
			printf("     Modify Booking\n");

			newReceipt.ticketInfo.startDate = selectDate();
			newReceipt.ticketInfo.noPax = noOfPax();
			selectPlace(newReceipt.departPlace);
			selectTrain(newReceipt.trainNo);
			selectPayment(newReceipt.paymentMethod);

			FILE* readNo = fopen("train.txt", "r");
			if (readNo == NULL) {
				printf("Error Opening File.\n");
				system("pause");
				ticketBookingMenu();
				return;
			}

			//while (fscanf(selPlace, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d:%d|%d:%d|%d|%lf\n",
			while (fscanf(readNo, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d|%d|%d|%lf\n",
				&train.trainNo, &train.trainType, &train.departPlace, &train.destination,
				&train.trainInfo.dateDepAvailable.day, &train.trainInfo.dateDepAvailable.month, &train.trainInfo.dateDepAvailable.year,
				&train.trainInfo.timeDepAvailable, &train.trainInfo.timeDestAvailable, &train.trainInfo.seatStillAvailable, &train.trainInfo.fare) != EOF) {

				if (strcmp(newReceipt.trainNo, train.trainNo) == 0) {
					printf("The fare of your trip: RM%.2lf\n", train.trainInfo.fare);
				}
			}

			fclose(readNo);

			newReceipt.paymentAmount = newReceipt.ticketInfo.noPax * train.trainInfo.fare;

			strcpy(newReceipt.receiptId, receipt[self].receiptId);

			printf("\n========================\n");
			printf("         Receipt\n");
			printf("========================\n");
			printf("Receipt Id     : %s\n", newReceipt.receiptId);
			printf("Train No       : %s\n", newReceipt.trainNo);
			printf("Date           : %02d/%02d/%d\n", newReceipt.ticketInfo.startDate.day, newReceipt.ticketInfo.startDate.month, newReceipt.ticketInfo.startDate.year);
			printf("Pax            : %d\n", newReceipt.ticketInfo.noPax);
			printf("Payment Method : %s\n", newReceipt.paymentMethod);
			printf("Amount         : RM%.2lf\n", newReceipt.paymentAmount);

			FILE* modify = fopen("receipt.bin", "wb");
			if (modify == NULL) {
				printf("Error Opening File.\n");
				system("pause");
				ticketBookingMenu();
				return;
			}

			receipt[self] = newReceipt;

			//modify into file
			for (int j = 0; j < i; j++) {
				fwrite(&receipt[j], sizeof(Payment), 1, modify);
			}

			fclose(modify);

			printf("\nYour trip modified successfully.\n\n");
			system("pause");
			ticketBookingMenu();
			break;
		case 'N':
			do {
				printf("\nDo you want to continue modify your trip?\n");
				printf("Yes'Y'/ No'N': ");
				rewind(stdin);
				scanf(" %c", &choice);
				choice = toupper(choice);

				switch (choice) {
				case 'Y':
					system("pause");
					modifyBooking(); break;
				case 'N':
					ticketBookingMenu(); break;
				default:
					printf("Invalid Choice. Please enter again.\n\n"); break;
				}
			} while (choice != 'Y'); break;
		default:
			printf("Invalid Choice. Please enter again.\n\n"); break;
		}
	} while (receiptChoice != 'Y');

}

void deleteBooking() {
	Payment receipt[100], newReceipt;
	char receiptChoice, choice1, choice2, choice3;
	char id[9];
	int i = 0, self = 0, j = 0;

	system("cls");
	printf("\n========================\n");
	printf("     Delete Booking\n");
	printf("========================\n");
	printf("Please enter your Receipt Id: ");
	rewind(stdin);
	scanf(" %8s", id);

	FILE* read = fopen("receipt.bin", "rb");
	if (read == NULL) {
		printf("Error Opening File.\n");
		system("pause");
		ticketBookingMenu();
		return;
	}

	while (fread(&receipt[i], sizeof(Payment), 1, read) != 0) {
		if (strcmp(receipt[i].receiptId, id) == 0) {
			printf("\n========================\n");
			printf("        Receipt\n");
			printf("========================\n");
			printReceipt(receipt[i]);
			self = i;
		}
		i++;
	}
	fclose(read);

	FILE* delete;
	delete = fopen("receipt.bin", "wb");
	if (delete == NULL) {
		printf("Error Opening File.\n");
		system("pause");
		ticketBookingMenu();
		return;
	}

	do {
		printf("\nIs this your receipt?\n");
		printf("Yes'Y'/ No'N': ");
		rewind(stdin);
		scanf(" %c", &receiptChoice);
		receiptChoice = toupper(receiptChoice);

		switch (receiptChoice) {
		case 'Y':
			do {
				printf("\nAre you sure want to delete your trip?\n");
				printf("Yes'Y'/ No'N': ");
				rewind(stdin);
				scanf(" %c", &choice1);
				choice1 = toupper(choice1);

				switch (choice1) {
				case 'Y':
					for (int j = 0; j < i; j++) {
						//if the file is the file that selected to be delete
						if (j == self) {
							continue;
						}
						//write the else data into the file
						else {
							fwrite(&receipt[j], sizeof(Payment), 1, delete);
						}
					}
					fclose(delete);

					printf("Your trip deleted successfully.\n");
					system("pause");
					ticketBookingMenu();
					break;
				case 'N':
					fclose(delete);
					do {
						printf("\nDo you want to continue?\n");
						printf("Yes'Y'/ No'N': ");
						rewind(stdin);
						scanf(" %c", &choice2);
						choice2 = toupper(choice2);

						switch (choice2) {
						case 'Y':
							system("pause");
							deleteBooking(); break;
						case 'N':
							system("pause");
							ticketBookingMenu(); break;
						default:
							printf("Invalid Choice. Please enter again.\n\n"); break;
						}
					} while (choice2 != 'Y'); break;
				default:
					fclose(delete);
					printf("Invalid Choice. Please enter again.\n\n"); break;
				}
			} while (choice1 != 'Y'); break;
		case 'N':
			fclose(delete);
			do {
				printf("\nDo you want to continue?\n");
				printf("Yes'Y'/ No'N': ");
				rewind(stdin);
				scanf(" %c", &choice3);
				choice3 = toupper(choice3);

				switch (choice3) {
				case 'Y':
					system("pause");
					deleteBooking(); break;
				case 'N':
					system("pause");
					ticketBookingMenu(); break;
				default:
					printf("Invalid Choice. Please enter again.\n\n"); break;
				}
			} while (choice3 != 'Y'); break;
		default:
			fclose(delete);
			printf("Invalid Choice. Please enter again.\n\n"); break;
		}
	} while (receiptChoice != 'Y');
}

void reportBooking() {
	FILE* report;
	Payment receipt;
	Date reportDate;
	int total = 0;

	report = fopen("receipt.bin", "rb");

	if (report == NULL) {
		printf("Error Opening File.\n");
		system("pause");
		reportMenu();
	}

	system("cls");
	printf("\n========================\n");
	printf("         Report\n");
	printf("========================\n");
	printf("Please enter date to found(DD/MM/YYYY): ");
	rewind(stdin);
	scanf("%2d/%2d/%4d", &reportDate.day, &reportDate.month, &reportDate.year);

	while (fread(&receipt, sizeof(Payment), 1, report) != 0) {
		if ((reportDate.day == receipt.ticketInfo.startDate.day) && (reportDate.month == receipt.ticketInfo.startDate.month) && (reportDate.year == receipt.ticketInfo.startDate.year)) {
			printf("\n");
			printReceipt(receipt);
			total += receipt.ticketInfo.noPax;
			printf("\nTotal Booking orders : %d\n", total);
		}
		else {
			printf("\nNo Booking Found.\n");
		}
	}

	fclose(report);
	system("pause");
}


// Ticket Booking Menu
int ticketBookingMenu() {
	int choice;

	do {
		system("cls");
		printf("========================\n");
		printf("\t  Menu\n");
		printf("========================\n");
		printf("1. Add Booking\n");
		printf("2. Display Booking\n");
		printf("3. Modify Booking\n");
		printf("4. Delete Booking\n");
		printf("5. Exit\n");
		printf("\nYour Choice(1/2/3/4/5): ");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			addBooking();
			break;
		case 2:
			displayBooking();
			break;
		case 3:
			modifyBooking();
			break;
		case 4:
			deleteBooking();
			break;
		case 5:
			return;
			break;
		default:
			printf("Invalid Choice.\n\n");
			break;
		}
	} while (choice != 5);

	return 0;
}


// Main 
main() {
	int option;
	do {
		clearScreen();
		printf("           @@@@@@@                  @@@@@                                            @              \n");
		printf("         @@       @@@@             @     @                                      @@@@   @@           \n");
		printf("         @            @@          @@        @@                                @           @         \n");
		printf("       @@              @         @@           @                              @             @        \n");
		printf("      @                @         @@    \033[31mMars\033[0m    @@           @@  @   @@       @@             @@      \n");
		printf("      @@               @           @             @         @            @     @@@            @      \n");
		printf("        @@@@@    @@@ @@@           @             @       @@              @      @@          @@      \n");
		printf("              @@                     @@     @  @@       @@       \033[33mNcD\033[0m       @        @@@@     @@     \n");
		printf("        @@ @@                          @@@@@            @@               @@           @   @@        \n");
		printf("       @@   @@                                           @@         @    @                          \n");
		printf("      @      @                                                 @@@@   @                             \n");
		printf("     @@    @@@                                                                                      \n");
		printf("       @@  @   @      @@"); printf("\033[35m"); printf("       Welcome"); printf("\033[0m"); printf("\033[36m"); printf("          1. Staff"); printf("\033[0m"); printf("\033[34m"); printf("          2. Member"); printf("\033[0m"); printf("\033[32m"); printf("         3. Exit"); printf("\033[0m");
		printf("\n        @@@ @@@@@@@@@ @   @@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@   \n");
		printf("         @@ @@ @@@@ @ @@ @@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@   \n");
		printf("       @@@@@@@@@@ @@@ @@  @@ @@@@@@@@@@ @@   @ @@@@@@@@@@ @@   @ @@@@@@@@@@ @@   @ @@@@@@@@@@@@@    \n");
		printf("      @               @@  @@ @@@@@@@@@@ @@   @ @@@@@@@@@@ @@   @ @@@@@@@@@@ @@   @ @@@@@@@@@@@@@    \n");
		printf("      @               @@  @@ @@@@@@@@@@ @@   @ @@@@@@@@@@ @@   @ @@@@@@@@@@ @@   @ @@@@@@@@@@ @@    \n");
		printf("     @@         @@@@@@@@  @@            @@   @            @@   @            @@   @            @@    \n");
		printf("    @@@@@@@@@@@@@@   @@@@@@@ @@@    @@@ @@@@@@ @@@    @@@ @@@@@@ @@@    @@@ @@@@@@ @@@    @@@ @@    \n");
		printf("       @@@ @@@  @@@  @@@@@@@@@ @@@@@@ @@@@@@@@@@ @@@@@@ @@@@@@@@@@  @@@@@ @@@@@@@@@@ @@@@@@ @@@@    \n");
		printf("        @@@@@    @@@@@       @@@@  @@@@@       @@@@  @@@@@       @@@@  @@@@@       @@@@  @@@@@\n");

		printf("\n\n\n\nSelect your option (1-3) : ");
		rewind(stdin);
		scanf("%d", &option);
	} while (option < 1 || option > 3);


	switch (option) {
	case 1:
		sModuleMain();
		break;
	case 2:
		mModuleMain();
		break;
	case 3:
		exit(-1);
		break;
	}
}