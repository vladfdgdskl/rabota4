#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <locale>

using namespace std;

const int CHILDREN_COUNT = 20;
const int TOP_GIRLS_COUNT = 5;

enum Gender
{
    Boy = 0,
    Girl = 1
};

struct Date
{
    int day;
    int month;
    int year;
};

struct Child
{
    char surname[30];
    char name[30];
    Gender gender;
    int height;
    Date birthDate;
};



void child(const Child& child)
{
    cout << left << setw(15) << child.surname
        << setw(15) << child.name;

    if (child.gender == Boy)
    {
        cout << setw(12) << "М";
    }
    else
    {
        cout << setw(12) << "Д";
    }

    cout << setw(8) << child.height
        << right << setfill('0')
        << setw(2) << child.birthDate.day << "."
        << setw(2) << child.birthDate.month << "."
        << child.birthDate.year
        << setfill(' ') << left
        << endl;
}

void children(const Child children[], int size)
{
    

    for (int i = 0; i < size; i++)
    {
        child(children[i]);
    }

    cout << endl;
}

bool readfil(Child children[], int size, const char* fileName)
{
    ifstream fin(fileName);

    if (!fin.is_open())
    {
        return false;
    }

    char surname[30];
    int genderValue;

    while (fin >> surname >> genderValue)
    {
        for (int i = 0; i < size; i++)
        {
            if (strcmp(children[i].surname, surname) == 0)
            {
                if (genderValue == 0)
                {
                    children[i].gender = Boy;
                }
                else
                {
                    children[i].gender = Girl;
                }
            }
        }
    }

    fin.close();
    return true;
}

double boyhei(const Child children[], int size)
{
    int sum = 0;
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (children[i].gender == Boy)
        {
            sum += children[i].height;
            count++;
        }
    }

    if (count == 0)
    {
        return 0;
    }

    return (double)sum / count;
}

int talGR(const Child children[], int size, Child tallestGirls[])
{
    Child girls[CHILDREN_COUNT];
    int girlsCount = 0;

    for (int i = 0; i < size; i++)
    {
        if (children[i].gender == Girl)
        {
            girls[girlsCount] = children[i];
            girlsCount++;
        }
    }

    for (int i = 0; i < girlsCount - 1; i++)
    {
        int maxIndex = i;

        for (int j = i + 1; j < girlsCount; j++)
        {
            if (girls[j].height > girls[maxIndex].height)
            {
                maxIndex = j;
            }
        }

        Child temp = girls[i];
        girls[i] = girls[maxIndex];
        girls[maxIndex] = temp;
    }

    int count = TOP_GIRLS_COUNT;

    if (girlsCount < TOP_GIRLS_COUNT)
    {
        count = girlsCount;
    }

    for (int i = 0; i < count; i++)
    {
        tallestGirls[i] = girls[i];
    }

    return count;
}

void familia(Child children[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < size; j++)
        {
            if (strcmp(children[j].surname, children[minIndex].surname) < 0)
            {
                minIndex = j;
            }
        }

        Child temp = children[i];
        children[i] = children[minIndex];
        children[minIndex] = temp;
    }
}

void DR(const Child children[], int size)
{
    time_t now = time(nullptr);
    tm* date = localtime(&now);
    int month = date->tm_mon + 1;
    bool found = false;

    

    for (int i = 0; i < size; i++)
    {
        if (children[i].birthDate.month == month)
        {
            child(children[i]);
            found = true;
        }
    }

    cout << endl;
}

void writefile(const Child children[], int size, const char* fileName)
{
    ofstream fout(fileName, ios::binary);

    

    fout.write((const char*)children, sizeof(Child) * size);
    fout.close();
}

int readfile(Child children[], int maxSize, const char* fileName)
{
    ifstream fin(fileName, ios::binary);

    

    int count = 0;

    while (count < maxSize && fin.read((char*)&children[count], sizeof(Child)))
    {
        count++;
    }

    fin.close();
    return count;
}

int main()
{
    setlocale(LC_ALL, "");

    Child children[CHILDREN_COUNT] =
    {
        {"Ivanov", "Artem", Boy, 142, {15, 1, 2012}},
        {"Petrova", "Anna", Girl, 151, {4, 4, 2011}},
        {"Sidorov", "Maxim", Boy, 148, {21, 9, 2012}},
        {"Kuznetsova", "Maria", Girl, 160, {11, 6, 2011}},
        {"Smirnov", "Daniil", Boy, 139, {9, 12, 2013}},
        {"Vasileva", "Elena", Girl, 155, {26, 4, 2012}},
        {"Popov", "Ilya", Boy, 150, {3, 3, 2011}},
        {"Sokolova", "Daria", Girl, 158, {18, 10, 2011}},
        {"Morozov", "Nikita", Boy, 145, {30, 7, 2012}},
        {"Novikova", "Sofia", Girl, 162, {7, 11, 2010}},
        {"Fedorov", "Kirill", Boy, 153, {13, 4, 2011}},
        {"Mikhailova", "Polina", Girl, 149, {25, 2, 2013}},
        {"Alekseev", "Roman", Boy, 147, {5, 8, 2012}},
        {"Lebedeva", "Alina", Girl, 157, {17, 5, 2011}},
        {"Egorov", "Timur", Boy, 154, {22, 4, 2011}},
        {"Pavlova", "Ksenia", Girl, 164, {1, 1, 2010}},
        {"Kozlov", "Matvey", Boy, 141, {12, 6, 2013}},
        {"Stepanova", "Victoria", Girl, 159, {29, 4, 2011}},
        {"Orlov", "Gleb", Boy, 146, {8, 10, 2012}},
        {"Nikolaeva", "Ekaterina", Girl, 156, {20, 9, 2011}}
    };

    cout << "Ученики:" << endl;
    children(children, CHILDREN_COUNT);

    bool ok = readfil(children, CHILDREN_COUNT, "gender.txt");

    

    

    cout << "" << endl;
    children(children, CHILDREN_COUNT);

    cout << "Средний рост мальчиков "
        << fixed << setprecision(2)
        << boyhei(children, CHILDREN_COUNT)
        << " см" << endl << endl;

    Child tallestGirls[TOP_GIRLS_COUNT];
    int girlsCount = talGR(children, CHILDREN_COUNT, tallestGirls);

    cout << "высокие девочки" << endl;
    children(tallestGirls, girlsCount);

    familia(children, CHILDREN_COUNT);

    cout << "Сортировка" << endl;
    children(children, CHILDREN_COUNT);

    cout << "поиск" << endl;
    bool found = false;
    

    for (int i = 0; i < CHILDREN_COUNT; i++)
    {
        if (strcmp(children[i].surname, "Ivanov") == 0)
        {
            child(children[i]);
            found = true;
        }
    }

    

    for (int i = 0; i < CHILDREN_COUNT; i++)
    {
        if (strcmp(children[i].surname, "Ivanov") == 0)
        {
            children[i].height = 150;
            cout << "Данные Ivanov изменены" << endl << endl;
            break;
        }
    }

    cout << "др" << endl;
    DR(children, CHILDREN_COUNT);

    writefile(children, CHILDREN_COUNT, "children.dat");

    Child childrenFromFile[CHILDREN_COUNT];
    int count = readfile(childrenFromFile, CHILDREN_COUNT, "children.dat");

    cout << "файл" << endl;
    children(childrenFromFile, count);

    return 0;
}