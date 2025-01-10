#include <iostream>
#include <fstream>

using namespace std;
#define tak_hingga 999

int jumlah_simpul;
int jarak_terpendek(int jarak[], bool titik_terkunjungi[], int n) {
    int penampung_jarak = tak_hingga;
    int minVertex = -1;

    for (int v = 0; v < n; v++) {
        if (!titik_terkunjungi[v] && jarak[v] < penampung_jarak) {
            penampung_jarak = jarak[v];
            minVertex = v;
        }
    }

    return minVertex;
}

void print_rute(int titik_terakhir[], int v) {
    if (titik_terakhir[v] == -1)
        return;



    print_rute(titik_terakhir, titik_terakhir[v]);
    cout << " -> " << v;

    //ofstream hasil_txt;
    //hasil_txt.open("hasil_perhitungan.txt", ios::app);
    //hasil_txt << " -> " << v;
    //hasil_txt.close();
}

void print_hasil(int jarak[], int titik_terakhir[], int titik_awal, int n) {
    cout << "Jarak Terpendek dari Titik Awal " << titik_awal << " ke Setiap Titik:" << endl;

    ofstream hasil_txt;

    hasil_txt.open("hasil_perhitungan.txt", ios::trunc);

    for (int v = 0; v < n; v++) {
        cout << "Titik " << v << ": ";
        hasil_txt << "Titik " << v << ": ";
        if (jarak[v] == tak_hingga) {
            cout << "Tidak Ada Jalur Terhubung" << endl;
            hasil_txt << "Tidak Ada Jalur Terhubung" << endl;
        } else {
            cout << jarak[v] << " (Jalur: " << titik_awal;
            hasil_txt << jarak[v] << " (Jalur: " << titik_awal;
            print_rute(titik_terakhir, v);
            cout << ")" << endl;
            hasil_txt << ")" << endl;
        }
    }
    hasil_txt.close();
}

void Dijkstra(int Matriks[5][5], int titik_awal, int n) {
    int jarak[5];
    int titik_terakhir[5];
    bool titik_terkunjungi[5];

    for (int v = 0; v < n; v++) {
        jarak[v] = tak_hingga;
        titik_terakhir[v] = -1;
        titik_terkunjungi[v] = false;
    }

    jarak[titik_awal] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = jarak_terpendek(jarak, titik_terkunjungi, n);
        titik_terkunjungi[u] = true;

        for (int v = 0; v < n; v++) {
            if (!titik_terkunjungi[v] && Matriks[u][v] && jarak[u] != tak_hingga && jarak[u] + Matriks[u][v] < jarak[v]) {
                jarak[v] = jarak[u] + Matriks[u][v];
                titik_terakhir[v] = u;
            }
        }
    }

    print_hasil(jarak, titik_terakhir, titik_awal, n);
}


int main() {
    string pilihan_awal, pilihan_akhir, ulang_simpul;

    cout << "-------------------------------------------------------" << endl;
    cout << "Aplikasi Penentu Rute Terpendek - Kelompok 7" << endl;
    cout << "-------------------------------------------------------" << endl << endl;

    do {
        cout << "Apakah Anda ingin menghitung Jarak Lintasan Terpendek? (y/t)" << endl;
        cin >> pilihan_awal;

        if (pilihan_awal == "y") {
            // Menghitung jarak lintasan terpendek
            cout << "Masukkan Jumlah Simpul dalam Graf : ";
            cin >> jumlah_simpul;

            int Matriks[5][5];

            cout << "Masukkan matriks ketetanggaan (0 untuk tidak ada sisi, angka lain untuk bobot sisi):" << endl;
            for (int i = 0; i < jumlah_simpul; i++) { // baris
                for (int j = 0; j < jumlah_simpul; j++) { //kolom
                    cin >> Matriks[i][j];
                }
            }

            do {
                int titik_awal;
                cout << "Masukkan titik awal: ";
                cin >> titik_awal;

                ofstream hasil_txt;

                hasil_txt.open("hasil_perhitungan.txt", ios::trunc);

                Dijkstra(Matriks, titik_awal, jumlah_simpul);

                hasil_txt.close();

                cout << endl << "Apakah Anda ingin mencoba titik lainnya? (y/t)" << endl;
                cin >> ulang_simpul;
            } while (ulang_simpul == "y");


            cout << endl << "Apakah Anda Ingin Menghitung Graf Lainnya? (y/t)" << endl;
            cin >> pilihan_akhir;

            while (pilihan_akhir != "y" && pilihan_akhir != "t") {
                cout << "Mohon Pilih dengan Benar" << endl;
                cout << "Apakah Anda Ingin Menghitung Lagi? (y/t)" << endl;
                cin >> pilihan_akhir;
            }
        }
    } while (pilihan_akhir == "y");

    cout << "Terima Kasih..." << endl;
    return 0;
}
