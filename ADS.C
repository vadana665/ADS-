#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
#include <time.h> 
#define HASH_TABLE_SIZE 100 
#define MAX_LOGIN_ATTEMPTS 3 
#define ACCOUNT_LOCK_DURATION 300  
typedef struct { 
    char username[50]; 
    char password[64]; 
    time_t lastLogin; 
    int loginAttempts; 
    bool locked; 
    char email[50]; 
} User; 
typedef struct HashNode { 
    User user; 
    struct HashNode *next; 
} HashNode; 
typedef struct { 
    HashNode *table[HASH_TABLE_SIZE]; 
} Hashtable; 
int hash(char *key) { 
    int hash = 0; 
    while (*key) { 
        hash += *key; 
       key++; 
   } 
    return hash % HASH_TABLE_SIZE; 
} 
User createUser(char *username, char *password, char *email) { 
 User newUser; 
    strcpy(newUser.username, username); 
    strcpy(newUser.password, password); 
    newUser.lastLogin = 0; 
    newUser.loginAttempts = 0; 
    newUser.locked = false; 
    strcpy(newUser.email, email); 
    return newUser; } 
HashNode *createHashNode(User user) { 
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode)); 
    newNode->user = user; 
    newNode->next = NULL; 
   return newNode; } 
void insertUser(Hashtable *hashTable, User user) { 
    int index = hash(user.username); 
    HashNode *newNode = createHashNode(user); 
    newNode->next = hashTable->table[index]; 
    hashTable->table[index] = newNode; } 
User *findUser(Hashtable *hashTable, char *username) { 
    int index = hash(username); 
    HashNode *current = hashTable->table[index]; 
    while (current != NULL) { 
        if (strcmp(current->user.username, username) == 0) { 
      return &(current->user);   } 
        current = current->next;     } 
    return NULL; } 
bool isAccountLocked(User *user) { 
    if (user->locked) { 
        time_t currentTime; 
        time(&currentTime); 
        if (currentTime - user->lastLogin < ACCOUNT_LOCK_DURATION) { 
            return true; 
  } else { 
            user->locked = false; 
            user->loginAttempts = 0; 
           return false;   }    }    return false; } 
void loginUser(Hashtable *hashTable) { 
    char username[50]; 
    char password[50]; 
    printf("Enter your username: "); 
 scanf("%s", username); 
    User *user = findUser(hashTable, username); 
    if (user != NULL) { 
        if (isAccountLocked(user)) { 
            printf("Account locked. Try again later.\n"); 
           return;     } 
        printf("Enter your password: "); 
        scanf("%s", password); 
 unsigned int hash = 0;
    while (*password) {
        hash = (hash << 5) + (*password)++; } 
    snprintf(password, 11,"%u",hash);
    if (strcmp(user->password, password) == 0) { 
     printf("Login successful! Welcome, %s!\n", username); 
     user->loginAttempts = 0;  
 } else {    printf("Invalid username or password. Please try again.\n"); 
            user->loginAttempts++; 
            if (user->loginAttempts >= MAX_LOGIN_ATTEMPTS) { 
             printf("Too many failed attempts. Your account is locked.\n"); 
                user->locked = true; 
  time(&user->lastLogin); 
  }}}
 else {        printf("User not found. Please register.\n");     } } 
void resetPassword(Hashtable *hashTable) { 
    char username[50]; 
    char email[50],str[50]; 
    printf("Enter your username: "); 
    scanf("%s", username); 
 User *user = findUser(hashTable, username); 
    if (user != NULL) {     if (isAccountLocked(user)) { 
            printf("Account locked. Password reset not allowed.\n"); 
            return;       } 
        printf("Enter the email associated with your account: "); 
        scanf("%s", email); 
        if (strcmp(user->email, email) == 0) { 
            char newPassword[50]; 
       printf("Enter your new password: "); 
    scanf("%s", str); 
           unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + (*str)++;    }
    snprintf(newPassword, 11,"%u",hash);
           strcpy(user->password, newPassword); 
            printf("Password reset successful!\n");  } else { 
       printf("Invalid email. Password reset failed.\n"); 
        }    } else { 
       printf("User not found. Please register.\n");    } } 
void registerUser(Hashtable *hashTable) { 
    char username[50]; 
    char password[50]; 
    char email[50];
    char str[50];
    printf("Enter a new username: "); 
    scanf("%s", username); 
    if (findUser(hashTable, username) != NULL) { 
        printf("Username already exists. Choose a different one.\n"); 
        return;   } 
 printf("Enter a password: "); 
    scanf("%s", str); 
 printf("Enter your email: "); 
    scanf("%s", email); 
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + (*str)++; }
    snprintf(password, 11,"%u",hash);
    User newUser = createUser(username, password, email); 
    insertUser(hashTable, newUser); 
    printf("User registered successfully!\n"); 
int main() {   Hashtable userTable; 
    for (int i = 0; i < HASH_TABLE_SIZE; i++) { 
        userTable.table[i] = NULL;  } 
    int choice; 
    do {
       printf("\nUser Authentication System\n"); 
        printf("1. Register\n"); 
        printf("2. Login\n"); 
        printf("3. Reset Password\n"); 
        printf("4. Exit\n"); 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
        switch (choice) { 
           case 1: 
                registerUser(&userTable); 
                break; 
            case 2:      loginUser(&userTable); 
                break; 
            case 3:  resetPassword(&userTable); 
               break; 
            case 4: 
                printf("Exiting...\n"); 
                break; 
            default: 
                printf("Invalid choice. Please try again.\n"); 
        }
    } while (choice!= 4);   return 0; 
}
