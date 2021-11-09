#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

int it_counter = 0; //лічильник вводу квартир для пошуку

//структура або параметри квартири, тип даних Flat
struct Flat{
    double square;
    int num_bedr;
    int num_wc;
    int dist_min;
    bool is_commercial; //true - commercial, false - living
    double cost;
};

//функція заповнення початкових даних та пошукових параметрів,
//навчальні знаення записуються у вектор даних flats типу Flat
void fill (bool is_it_first_run, vector <Flat> &flats_to_fill) {   //булієва функція is_it_first_run позначає перший
    while (true) {                                                 //навчальний запуск функції при значенні true
        Flat tmpFlat;                                              //та другий, "предиктивний", при значенні false,
        if (is_it_first_run){                                      //відрізняються вони наявністю запису ціни квартири
            cout << "Enter the square value (enter 0 to stop learning):" << endl;
        }else{
            cout << "Now enter the square value for your flat of dream:" << endl;
        }
        cin >> tmpFlat.square;
        if (tmpFlat.square == 0) {
            break;
        }

        if (tmpFlat.square > 500 || tmpFlat.square < 10) {         //sanity check: при вводі якогось дивного значення
            cout << "incorrect value, please try again" << endl;   //ми відправляємо юзера перезаповнити параметри
            fill(is_it_first_run,flats_to_fill);                //квартири за допомогою рекурсії, а цю квартиру
            break;                                                 //із дивними параметрами до вектору додано не буде.
        }                                                          //перевірка типу даних не є суттєвою, тому що
                                                                   //у випадку неправильного вводу випаде помилка
        cout << "Enter the number of bedrooms:" << endl;
        cin >> tmpFlat.num_bedr;
        if (tmpFlat.num_bedr > 5 || tmpFlat.num_bedr < 1) {
            cout << "incorrect value, please try again" << endl;
            fill(is_it_first_run,flats_to_fill);
            break;
        }

        cout << "Enter the number of toilets:" << endl;
        cin >> tmpFlat.num_wc;
        if (tmpFlat.num_wc > 5 || tmpFlat.num_wc < 1) {
            cout << "incorrect value, please try again" << endl;
            fill(is_it_first_run,flats_to_fill);
            break;
        }

        cout << "Enter the distance to the nearest subway station on foot (in minutes):" << endl;
        cin >> tmpFlat.dist_min;
        if (tmpFlat.dist_min > 180 || tmpFlat.dist_min < 1) {
            cout << "incorrect value, please try again" << endl;
            fill(is_it_first_run,flats_to_fill);
            break;
        }

        cout << "Enter the type of flat - 1 for commercial or 0 for living:" << endl;
        cin >> tmpFlat.is_commercial;

        if (is_it_first_run) {
            cout << "Enter the cost:" << endl;
            cin >> tmpFlat.cost;
            if (tmpFlat.cost > 1000000000 || tmpFlat.cost < 50000) {
                cout << "incorrect value, please try again" << endl;
                fill(is_it_first_run,flats_to_fill);
                break;
            }
        }
        flats_to_fill.push_back(tmpFlat);
        if (!is_it_first_run) break;  //закінчення функції після вводу "предиктивної" частини
    }
}
//функція навчання та розрахунку балів квартир з початковіх даних
double learn (vector <Flat> flats_db){
    vector <int> points;
    for (int i = 0; i < flats_db.size(); ++i) {
        int tmp_points = flats_db.at(i).square * 1 + flats_db.at(i).num_bedr * 20 + flats_db.at(i).num_wc * 10;
        if (flats_db.at(i).is_commercial) tmp_points += 100;
        if (flats_db.at(i).dist_min < 6) {                     //у системі оцінювання квартири за кожен м2 видається
            tmp_points += 50;                                  //1 поінт, за кожну кімнату/спальню 20, за санвузол 10,
        } else if (flats_db.at(i).dist_min < 11) {             //якщо приміщення комерційне, додається 100 поінтів,
            tmp_points += 20;                                  //за простою системою додаються бали за відстань до метро
        } else if (flats_db.at(i).dist_min < 21) {
            tmp_points += 10;
        }
        points.push_back(tmp_points);
    }

    //невеличкий метод розрахування середньої вартості одного поінту, множника
    double factor_average = 0;
    double tmp_sum = 0;
    for (int i = 0; i < flats_db.size(); ++i) {
        double tmp_factor = flats_db.at(i).cost / points[i];
        tmp_sum += tmp_factor;
        factor_average = tmp_sum / flats_db.size();
    }
    return factor_average;
}

//функція саме розрахунку вартості шуканої квартири шляхом підрахування її балів та домноження їх на ср. вартість поінту
void predict (double &average_factor, vector <Flat> &tmpFlat) {
    fill(false, tmpFlat);  //те саме друге заповнення параметрів квартири без вводу ціни

    vector <double> points;
    bool answer;

    for (int i = 0; i < tmpFlat.size(); i++) {
        int tmp_points = tmpFlat.at(i).square * 1 + tmpFlat.at(i).num_bedr * 20 + tmpFlat.at(i).num_wc * 10;
        if (tmpFlat.at(i).is_commercial) tmp_points += 100;
        if (tmpFlat.at(i).dist_min < 6) {
            tmp_points += 50;
        } else if (tmpFlat.at(i).dist_min < 11) {
            tmp_points += 20;
        } else if (tmpFlat.at(i).dist_min < 21) {
            tmp_points += 10;
        }
        points.push_back(tmp_points);
    }
    //просто захотілося щоб ціну було краще видно серед усього білого
    cout << "Average cost for the flat like this is ";
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 13);
    cout << points[it_counter] * average_factor << endl;
    SetConsoleTextAttribute(h, 7);

    it_counter++;

    //можливість вводити умовно незліченну кількість картир для пошуку
    cout << "do you want to continue searching for the flat of your dream?(1 for yes, 0 for no)" << endl;
    cin >> answer;
    if (answer) {
        predict(average_factor, tmpFlat);
    }
}


    int main() {

        vector<Flat> flats;
        vector<Flat> flatToPredict;

        fill(true, flats);

        double average_factor = learn(flats);

        predict(average_factor, flatToPredict);

        return 0;
    }