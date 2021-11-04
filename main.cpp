#include <iostream>
#include <vector>

using namespace std;

struct Flat{
    double square;
    int num_bedr;
    int num_wc;
    int dist_min;
    bool is_commercial; //true - commercial, false - living
    double cost;
};



void fill (bool is_it_first_run, vector <Flat> &flats_to_fill) {
    while (true) {
        Flat tmpFlat;
        if (is_it_first_run){
            cout << "Enter the square value (enter 0 to stop):" << endl;
        }else{
            cout << "Enter the square value for your flat:" << endl;
        }
        cin >> tmpFlat.square;
        if (tmpFlat.square == 0) break;
        if (tmpFlat.square > 500 || tmpFlat.square <= 10) {
            cout << "incorrect value, please try again" << endl;
            fill(true,flats_to_fill);                //при вводі якогось дивного значення ми відправляємо
            break;                                               //юзера перезаповнити параметри квартири, а цю квартиру
        }                                                       //із дивними параметрами до вектору додано не буде

        cout << "Enter the number of bedrooms:" << endl;
        cin >> tmpFlat.num_bedr;
        if (tmpFlat.num_bedr > 5 || tmpFlat.num_bedr < 1) {
            cout << "incorrect value, please try again" << endl;
            fill(true,flats_to_fill);
            break;
        }

        cout << "Enter the number of toilets:" << endl;
        cin >> tmpFlat.num_wc;
        if (tmpFlat.num_wc > 5 || tmpFlat.num_wc < 1) {
            cout << "incorrect value, please try again" << endl;
            fill(true,flats_to_fill);
            break;
        }

        cout << "Enter the distance to the nearest subway station on foot (in minutes):" << endl;
        cin >> tmpFlat.dist_min;
        if (tmpFlat.dist_min > 180 || tmpFlat.dist_min < 1) {
            cout << "incorrect value, please try again" << endl;
            fill(true,flats_to_fill);
            break;
        }

        cout << "Enter the type of flat - 1 for commercial or 0 for living:" << endl;
        cin >> tmpFlat.is_commercial;

        if (is_it_first_run) {
            cout << "Enter the cost:" << endl;
            cin >> tmpFlat.cost;
            if (tmpFlat.cost > 1000000000 || tmpFlat.cost < 100000) {
                cout << "incorrect value, please try again" << endl;
                fill(true,flats_to_fill);
                break;
            }
        }
        flats_to_fill.push_back(tmpFlat);
        if (is_it_first_run != true) break;
    }
}

double learn (vector <Flat> flats_db){
    vector <int> points;
    for (int i = 0; i < flats_db.size(); ++i) {
        int tmp_points = flats_db.at(i).square*1 + flats_db.at(i).num_bedr*20 + flats_db.at(i).num_wc*10;
        if (flats_db.at(i).is_commercial) tmp_points += 100;
        if (flats_db.at(i).dist_min < 5) {
            tmp_points += 50;
        } else if (flats_db.at(i).dist_min < 10){
            tmp_points += 20;
        } else if (flats_db.at(i).dist_min < 20) {
            tmp_points += 10;
        }
        points.push_back(tmp_points);
    }

    vector <double> factor;
    double factor_average = 0;
    double tmp_sum = 0;
    for (int i = 0; i < flats_db.size(); ++i) {
        double tmp_factor = flats_db.at(i).cost / points[i];
        factor.push_back(tmp_factor);
        tmp_sum += tmp_factor;
        factor_average = tmp_sum / flats_db.size();
    }
//    cout << points[0] << endl;
//    cout << points[1] << endl;
//    cout << factor.at(0) << endl;
//    cout << factor.at(1) << endl;
    cout << factor_average << endl;
    return factor_average;
}


void predict (double &average_factor, vector <Flat> &tmpFlat){
    fill (false, tmpFlat);
    int points = 0;

        points = tmpFlat.at(0).square * 1 + tmpFlat.at(0).num_bedr * 20 + tmpFlat.at(0).num_wc * 10;
        if (tmpFlat.at(0).is_commercial) points += 100;
        if (tmpFlat.at(0).dist_min < 5) {
            points += 50;
        } else if (tmpFlat.at(0).dist_min < 10){
            points += 20;
        } else if (tmpFlat.at(0).dist_min < 20) {
            points += 10;
        }

    cout << "average factor is  " << average_factor << endl;
    cout << "points for this flat " << points << endl;
    cout << "average cost for the flat like this is " << points*average_factor << endl;
}



int main() {

    vector <Flat> flats;
    vector <Flat> flatToPredict;

    fill(true,flats);
    double average_factor = learn(flats);

    predict(average_factor, flatToPredict);

    return 0;
}
