#include "main.h"
#include "pch.h"
#include <iostream>


using namespace std;

int compare_lists(Node* head1, Node* head2) {
    while (head1 && head2) {
        if (head1->hours != head2->hours || head1->date.day != head2->date.day ||
            head1->date.month != head2->date.month ||
            head1->date.year != head2->date.year ||
            strcmp(head1->name, head2->name) != 0 ||
            strcmp(head1->surname, head2->surname) != 0) {
            return 0;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    if (head1 == NULL && head2 == NULL)
        return 1;
    else
        return 0;
}

TEST(_parse_line, NormalInput) { /*return True*/

    char* line = (char*)malloc(sizeof(char) * 100);
    strcpy(line, "23.05.2020 Doe John 5");

    Node* New = parse_line(line);
    New->next = NULL;

    Node* Expected = (Node*)malloc(sizeof(Node));
    Expected->hours = 5;
    Expected->date.day = 23;
    Expected->date.month = 5;
    Expected->date.year = 2020;
    strcpy(Expected->name, "Serdar");
    strcpy(Expected->surname, "Dowran");
    Expected->next = NULL;

    EXPECT_TRUE(compare_lists(New, Expected));

    free(line);
    free(New);
    free(Expected);
}

TEST(_parse_line, NoInput) { /*return True*/

    char* line = (char*)malloc(sizeof(char) * 100);
    strcpy(line, "");

    Node* New = parse_line(line);

    EXPECT_TRUE(compare_lists(New, NULL));

    free(line);
    free(New);
}

TEST(_parse_line, IncompleteInput) { /*return True*/

    char* line = (char*)malloc(sizeof(char) * 100);
    strcpy(line, "23.05.2020 Dowran Serdar");

    Node* New = parse_line(line);

    EXPECT_TRUE(compare_lists(New, NULL));

    free(line);
    free(New);
}

TEST(_add_sort_list, AddToEmptyList) { 

    Node* head = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    New->hours = 5;
    New->date.day = 23;
    New->date.month = 5;
    New->date.year = 2020;
    strcpy(New->name, "Serdar");
    strcpy(New->surname, "Dowran");

    head = add_sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    Expected_Head->hours = 5;
    Expected_Head->date.day = 23;
    Expected_Head->date.month = 5;
    Expected_Head->date.year = 2020;
    strcpy(Expected_Head->name, "Serdar");
    strcpy(Expected_Head->surname, "Dowran");
    Expected_Head->next = NULL;

    EXPECT_TRUE(compare_lists(head, Expected_Head));

    free(New);
    free(Expected_Head);
}

TEST(_add_sort_list, AddToNonEmptyList) { /*return True*/

    Node* head = (Node*)malloc(sizeof(Node));
    head->hours = 10;
    head->date.day = 15;
    head->date.month = 7;
    head->date.year = 2021;
    strcpy(head->name, "Ayna");
    strcpy(head->surname, "Seyran");
    head->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    New->hours = 5;
    New->date.day = 23;
    New->date.month = 5;
    New->date.year = 2020;
    strcpy(New->name, "Serdar");
    strcpy(New->surname, "Dowran");

    head = add_sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    Expected_Head->hours = 5;
    Expected_Head->date.day = 23;
    Expected_Head->date.month = 5;
    Expected_Head->date.year = 2020;
    strcpy(Expected_Head->name, "Serdar");
    strcpy(Expected_Head->surname, "Dowran");

    Node* Expected_Second = (Node*)malloc(sizeof(Node));
    Expected_Second->hours = 10;
    Expected_Second->date.day = 15;
    Expected_Second->date.month = 7;
    Expected_Second->date.year = 2021;
    strcpy(Expected_Second->name, "Ayna");
    strcpy(Expected_Second->surname, "Seyran");
    Expected_Head->next = Expected_Second;
    Expected_Second->next = NULL;

    EXPECT_TRUE(compare_lists(head, Expected_Head));

    free(New);
    free(Expected_Head);
    free(Expected_Second);
}

TEST(_add_sort_list, AddToMiddleOfList) { /*return True*/

    Node* head = (Node*)malloc(sizeof(Node));
    head->hours = 5;
    head->date.day = 15;
    head->date.month = 5;
    head->date.year = 2021;
    strcpy(head->name, "Ayna");
    strcpy(head->surname, "Jemal");

    Node* Second = (Node*)malloc(sizeof(Node));
    Second->hours = 15;
    Second->date.day = 20;
    Second->date.month = 5;
    Second->date.year = 2021;
    strcpy(Second->name, "Bayram");
    strcpy(Second->surname, "Seyran");

    head->next = Second;
    Second->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    New->hours = 10;
    New->date.day = 18;
    New->date.month = 5;
    New->date.year = 2021;
    strcpy(New->name, "Chary");
    strcpy(New->surname, "Begench");

    head = add_sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    Expected_Head->hours = 5;
    Expected_Head->date.day = 15;
    Expected_Head->date.month = 5;
    Expected_Head->date.year = 2021;
    strcpy(Expected_Head->name, "Ayna");
    strcpy(Expected_Head->surname, "Jemal");

    Node* Expected_Middle = (Node*)malloc(sizeof(Node));
    Expected_Middle->hours = 10;
    Expected_Middle->date.day = 18;
    Expected_Middle->date.month = 5;
    Expected_Middle->date.year = 2021;
    strcpy(Expected_Middle->name, "Chary");
    strcpy(Expected_Middle->surname, "Begench");

    Node* Expected_Tail = (Node*)malloc(sizeof(Node));
    Expected_Tail->hours = 15;
    Expected_Tail->date.day = 20;
    Expected_Tail->date.month = 5;
    Expected_Tail->date.year = 2021;
    strcpy(Expected_Tail->name, "Bayram");
    strcpy(Expected_Tail->surname, "Seyran");

    Expected_Head->next = Expected_Middle;
    Expected_Middle->next = Expected_Tail;
    Expected_Tail->next = NULL;

    EXPECT_TRUE(compare_lists(head, Expected_Head));

    free(New);
    free(head);
    free(Second);
    free(Expected_Head);
    free(Expected_Middle);
    free(Expected_Tail);
}

TEST(_add_sort_list, AddWithSameHoursDifferentNames) { /*return True*/

    Node* head = (Node*)malloc(sizeof(Node));
    head->hours = 5;
    head->date.day = 10;
    head->date.month = 6;
    head->date.year = 2021;
    strcpy(head->name, "Ahal");
    strcpy(head->surname, "Seyran");
    head->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    New->hours = 5;
    New->date.day = 15;
    New->date.month = 6;
    New->date.year = 2021;
    strcpy(New->name, "Bayram");
    strcpy(New->surname, "Jemal");

    head = add_sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    Expected_Head->hours = 5;
    Expected_Head->date.day = 15;
    Expected_Head->date.month = 6;
    Expected_Head->date.year = 2021;
    strcpy(Expected_Head->name, "Bayram");
    strcpy(Expected_Head->surname, "Jemal");

    Node* Expected_Second = (Node*)malloc(sizeof(Node));
    Expected_Second->hours = 5;
    Expected_Second->date.day = 10;
    Expected_Second->date.month = 6;
    Expected_Second->date.year = 2021;
    strcpy(Expected_Second->name, "Ahal");
    strcpy(Expected_Second->surname, "Seyran");

    Expected_Head->next = Expected_Second;
    Expected_Second->next = NULL;

    EXPECT_TRUE(compare_lists(head, Expected_Head));

    free(New);
    free(Expected_Head);
    free(Expected_Second);
}

TEST(_count_hours, ListWithDifferentNames) { /*all return True*/

    Node* head = (Node*)malloc(sizeof(Node));
    head->date = { 1, 1, 2024 };
    strcpy(head->name, "Serdar");
    strcpy(head->surname, "Dowran");
    head->hours = 5;

    Node* Second = (Node*)malloc(sizeof(Node));
    Second->date = { 2, 1, 2024 };
    strcpy(Second->name, "Jeren");
    strcpy(Second->surname, "Dowran");
    Second->hours = 3;

    Node* Last = (Node*)malloc(sizeof(Node));
    Last->date = { 3, 1, 2024 };
    strcpy(Last->name, "Jennet");
    strcpy(Last->surname, "Shamyrat");
    Last->hours = 2;

    head->next = Second;
    Second->next = Last;
    Last->next = NULL;

    int count;
    HourCounter* result = count_hours(head, &count);
    EXPECT_STREQ(result[0].name, "Serdar");
    EXPECT_STREQ(result[0].surname, "Dowran");
    EXPECT_EQ(result[0].total, 5);

    EXPECT_STREQ(result[1].name, "Jeren");
    EXPECT_STREQ(result[1].surname, "Dowran");
    EXPECT_EQ(result[1].total, 3);


    EXPECT_STREQ(result[2].name, "Jennet");
    EXPECT_STREQ(result[2].surname, "Shamyrat");
    EXPECT_EQ(result[2].total, 2);

    free(result);
    free(head);
    free(Second);
    free(Last);
}

TEST(_count_hours, ListWithRecurringNames) { /*all return True*/

    Node* head = (Node*)malloc(sizeof(Node));
    head->date = { 1, 1, 2024 };
    strcpy(head->name, "Serdar");
    strcpy(head->surname, "Dowran");
    head->hours = 5;

    Node* Second = (Node*)malloc(sizeof(Node));
    Second->date = { 2, 1, 2024 };
    strcpy(Second->name, "Serdar");
    strcpy(Second->surname, "Dowran");
    Second->hours = 3;

    Node* Last = (Node*)malloc(sizeof(Node));
    Last->date = { 3, 1, 2024 };
    strcpy(Last->name, "Serdar");
    strcpy(Last->surname, "Dowran");
    Last->hours = 2;

    head->next = Second;
    Second->next = Last;
    Last->next = NULL;

    int count;
    HourCounter* result = count_hours(head, &count);

    EXPECT_EQ(count, 2);
    EXPECT_STREQ(result[0].name, "Serdar");
    EXPECT_STREQ(result[0].surname, "Dowran");
    EXPECT_EQ(result[0].total, 7);

    EXPECT_STREQ(result[1].name, "Jeren");
    EXPECT_STREQ(result[1].surname, "Dowran");
    EXPECT_EQ(result[1].total, 3);

    free(result);
    free(head);
    free(Second);
    free(Last);
}

TEST(_count_hours, EmptyList) { 

    Node* head = NULL;

    int count;
    HourCounter* result = count_hours(head, &count);

    EXPECT_EQ(count, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    cout << "RUN TEST" << endl;

    return RUN_ALL_TESTS();
}