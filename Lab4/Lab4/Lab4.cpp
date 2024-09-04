#include <iostream>
#include <assert.h>
#include <fstream>

using namespace std;

struct aminoAcid {
    size_t key;
    string value;
};

class AcidTable {
private:
    hash<string> hasher = hash<string>();

    int size = 0;
    aminoAcid* aminoAcids = new aminoAcid[0];
public:
    /// <summary>
    /// Creates amino acid
    /// </summary>
    /// <param name="codonString">String codon</param>
    /// <param name="aminoAcidString">String amino acid</param>
    /// <returns>aminoAcid object</returns>
    static aminoAcid createElement(const string& codonString, const string& aminoAcidString)
    {
        aminoAcid element;
        element.key = hash<string>()(codonString);
        element.value = aminoAcidString;
        return element;
    }

    class ElementIsNotFoundError {
    public:
        ElementIsNotFoundError(std::string message) : message{ message } {}
        string getMessage() const { return message; }
    private:
        string message;
    };

    /// <summary>
    /// Returns the number of objects stored
    /// </summary>
    /// <returns>Number of amino acids stored</returns>
    const int getSize() const {
        return this->size;
    }

    bool checkKey(const string& codonString) const {
        for (int i = 0; i < size; i++) {
            if (this->hasher(codonString) == this->aminoAcids[i].key)
                return 1;
        }
        return 0;
    }

    const string getAcid(const string& codonString)const {
        for (int i = 0; i < size; i++) {
            if (this->hasher(codonString) == this->aminoAcids[i].key)
                return this->aminoAcids[i].value;
        }
        throw(ElementIsNotFoundError("Could not find element by key"));
    }

    const string operator[](const string& codonString) const {
        return getAcid(codonString);
    }

    void insertObject(const string& codonString, const string& aminoAcidString) {
        if (codonString == "" || aminoAcidString == "")
            return;
        aminoAcid* newAminoAcids = new aminoAcid[this->size + 1];

        for (int i = 0; i < size; i++) {
            if (this->hasher(codonString) == this->aminoAcids[i].key) {
                delete[] newAminoAcids;
                return;
            }
            newAminoAcids[i] = this->aminoAcids[i];
        }
        delete[] this->aminoAcids;
        this->aminoAcids = newAminoAcids;
        this->aminoAcids[size++] = createElement(codonString, aminoAcidString);
    }

    void operator<<(const aminoAcid& acid) {
        aminoAcid* newAminoAcids = new aminoAcid[this->size + 1];
        for (int i = 0; i < size; i++) {
            if (acid.key == this->aminoAcids[i].key) {
                delete[] newAminoAcids;
                return;
            }
            newAminoAcids[i] = this->aminoAcids[i];
        }
        delete[] this->aminoAcids;
        this->aminoAcids = newAminoAcids;
        this->aminoAcids[size++] = acid;
    }

    void deleteKey(string codonString) {
        aminoAcid* newAminoAcids = new aminoAcid[this->size - 1];

        bool found = 0;

        for (int i = 0; i < size; i++) {
            if (this->hasher(codonString) != this->aminoAcids[i].key) {
                if (i - found + 1 != size)
                    newAminoAcids[i - found] = this->aminoAcids[i];
            }
            else {
                found = 1;
            }
        }

        if (found) {
            delete[] this->aminoAcids;
            this->aminoAcids = newAminoAcids;
            --this->size;
        }
        else {
            delete[] newAminoAcids;
            throw(ElementIsNotFoundError("Could not find element by key"));
        }
    }

    void deleteAll() {
        delete[] aminoAcids;
        aminoAcids = new aminoAcid[0];
        size = 0;
    }

    /// <summary>
    /// Default empty constructor
    /// </summary>
    AcidTable() {}

    /// <summary>
    /// Initialization constructor
    /// </summary>
    /// <param name="aminoAcidString">String amino acid</param>
    /// <returns>aminoAcid object</returns>
    AcidTable(const string& codonString, const string& aminoAcidString) {
        if (!(codonString == "" || aminoAcidString == ""))
            insertObject(codonString, aminoAcidString);
    }

    AcidTable(const AcidTable& acidTable) {
        this->size = acidTable.size;
        this->aminoAcids = new aminoAcid[this->size];
        for (int i = 0; i < this->size; i++) {
            this->aminoAcids[i] = acidTable.aminoAcids[i];
        }
    }

    /// <summary>
    /// Cross constructor
    /// </summary>
    /// <param name="acidTable1"></param>
    /// <param name="acidTable2"></param>
    AcidTable(const AcidTable& acidTable1, const AcidTable& acidTable2) {
        for (int i = 0; i < acidTable1.size; i++) {
            for (int j = 0; j < acidTable2.size; j++) {
                if (acidTable1.aminoAcids[i].key == acidTable2.aminoAcids[j].
                    key) {
                    if (acidTable1.aminoAcids[i].value
                        == acidTable2.aminoAcids[j].value) {

                        aminoAcid* newAminoAcids = new aminoAcid[this->size + 1];

                        for (int k = 0; k < size; k++) {
                            newAminoAcids[k] = this->aminoAcids[k];
                        }
                        delete[] this->aminoAcids;
                        this->aminoAcids = newAminoAcids;
                        aminoAcid newAminoAcid;
                        newAminoAcid.key = acidTable1.aminoAcids[i].key;
                        newAminoAcid.value = acidTable1.aminoAcids[i].value;
                        this->aminoAcids[size++] = newAminoAcid;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    AcidTable operator&&(AcidTable& acidTable) const {
        return AcidTable(*this, acidTable);
    }

    bool operator==(AcidTable& acidTable) const {
        int count = 0;
        if (this->size == acidTable.size) {
            for (int i = 0; i < this->size; i++) {
                for (int j = 0; j < acidTable.size; j++) {
                    if (this->aminoAcids[i].key ==
                        acidTable.aminoAcids[j].key) {
                        if (this->aminoAcids[i].value == acidTable.
                            aminoAcids[j].value)
                            ++count;
                        else
                            return 0;
                        break;
                    }
                }
            }
            if (count == this->size)
                return 1;
        }
        return 0;
    }

    ~AcidTable() {
        delete[] aminoAcids;
    }

    void writeFile(const string& path) const {
        ofstream fout(path, ofstream::out);
        for (int i = 0; i < size; i++) {
            fout << aminoAcids[i].key <<
                ' ' << aminoAcids[i].value << ' ';
        }
    }

    void insertFile(const string& path) {
        ifstream fin(path, ofstream::in);
        while (fin.peek() != EOF) {
            aminoAcid aminoAcid;
            fin >> aminoAcid.key >> aminoAcid.value;
            this->operator<<(aminoAcid);
        }
    }

    string* getAcidList(string keys[]) const {
        int length = -1;
        while (true) {
            try {
                (keys)[++length];
            }
            catch (exception ex) {
                break;
            }
        }
        string* ans = new string[length];
        for (int i = 0; i < length; i++) {
            try {
                ans[i] = this->getAcid(keys[i]);
            }
            catch (ElementIsNotFoundError) {
                ans[i] = "";
            }
        }
        return ans;
    }

};

int main() {
    AcidTable table("0", "0");
    assert(table.getSize() == 1);
    table.insertObject("2", "0");
    assert(table.getSize() == 2);
    table << AcidTable::createElement("3", "1");
    assert(table.getSize() == 3);
    table.deleteKey("0");
    assert(table.getSize() == 2);
    table << AcidTable::createElement("3", "1");
    assert(table.getSize() == 2);
    AcidTable table2 = AcidTable("2", "0");
    AcidTable res = AcidTable(table, table2);
    assert(res.getSize() == 1);
    assert(res == table2);
    AcidTable dummy = AcidTable();
    assert(dummy.getSize() == 0);
    assert((res && dummy) == dummy);
    assert(table.checkKey("2"));
    table2.operator<<(AcidTable::createElement("3", "1"));
    assert((table2 && table2) == table2);
    AcidTable ctable2(table2);
    assert((table2 && ctable2) == table2);
    ctable2.insertObject("1324", "2345");

    assert(ctable2["1324"] == "2345");
    assert(ctable2.getAcid("1324") == "2345");

    assert(!((table2 && ctable2) == ctable2));
    table.deleteAll();
    assert(table == dummy);
    ctable2.writeFile("test.conf");
    table.insertFile("test.conf");
    assert(table == ctable2);

    string nullList[2]={"qwerty", "ytrewq"};
    table.getAcidList(nullList);

    string keyList[3] = { "1324", "0", "2"};
    string *answerList = table.getAcidList(keyList);
    assert(answerList[0] == "2345");
    assert(answerList[1] == "");
    assert(answerList[2] == "0");


    string keyList2[4] = { "1324", "0", "2", "1"};
    string* answerList2 = table.getAcidList(keyList2);

    cout << "Tests passed" << endl;
}