#ifndef SAFE_ARRAY_COURSE_H
#define SAFE_ARRAY_COURSE_H

int const MAX_LINES = 10;

class course {

public:
    string name;
    string title;
    string description[MAX_LINES];

    course() : name(""), title("") { }

    course(string name, string title) : name(name), title(title) { }

    friend ostream &operator<<(ostream &, const course &);

    friend istream &operator>>(istream &, course &);
};

ostream &operator<<(ostream &out, const course &c) {
    out << c.name << ": " << c.title << "\n";

    int index = 0;
    while (c.description[index] != "") {
        out << c.description[index++] << "\n";
    }

    return out;
}

istream &operator>>(istream &in, course &c) {
    getline(in, c.name);
    getline(in, c.title);

    string line;
    getline(in, line);
    int number = 0;
    while (line != "") {
        c.description[number++] = line;
        getline(in, line);
    }

    return in;
}

#endif
