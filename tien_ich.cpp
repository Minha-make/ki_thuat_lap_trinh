#include "tien_ich.h"

// Cat khoang trang, tab va ky tu xuong dong o dau/cuoi chuoi de chuan hoa du lieu nhap.
string catKhoangTrang(string s) {
    int dau = 0;
    int cuoi = (int)s.length() - 1;

    while (dau <= cuoi && (s[dau] == ' ' || s[dau] == '\t' || s[dau] == '\r' || s[dau] == '\n')) {
        dau++;
    }
    while (cuoi >= dau && (s[cuoi] == ' ' || s[cuoi] == '\t' || s[cuoi] == '\r' || s[cuoi] == '\n')) {
        cuoi--;
    }

    string ketQua = "";
    for (int i = dau; i <= cuoi; i++) {
        ketQua += s[i];
    }
    return ketQua;
}

// Kiem tra chuoi co phai so nguyen khong am; dung truoc khi ep chuoi sang so.
bool laSoNguyen(string s) {
    s = catKhoangTrang(s);
    if (s == "") return false;

    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

// Chuyen chuoi dang so thanh double; ham nay dung chung cho ca so nguyen va so thuc.
double chuoiSangSo(string s) {
    double so = 0;
    double heSo = 0.1;
    bool sauDauCham = false;
    s = catKhoangTrang(s);

    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] == '.') {
            sauDauCham = true;
        } else if (s[i] >= '0' && s[i] <= '9') {
            if (!sauDauCham) {
                so = so * 10 + (s[i] - '0');
            } else {
                so += (s[i] - '0') * heSo;
                heSo /= 10;
            }
        }
    }
    return so;
}

// Nhap so nguyen trong khoang cho phep; lap lai den khi nguoi dung nhap hop le.
int nhapSo(string thongBao, int nhoNhat, int lonNhat) {
    string dong;
    int so;

    while (true) {
        cout << thongBao;
        getline(cin, dong);

        if (!laSoNguyen(dong)) {
            cout << "Nhap sai. Hay nhap so nguyen.\n";
            continue;
        }

        so = static_cast<int>(chuoiSangSo(dong));
        if (so < nhoNhat || so > lonNhat) {
            cout << "Gia tri phai tu " << nhoNhat << " den " << lonNhat << ".\n";
            continue;
        }

        return so;
    }
}

// Nhap chuoi khong rong va khong chua ky tu '|', vi '|' duoc dung de tach truong trong file.
string nhapChuoi(string thongBao) {
    string s;

    while (true) {
        cout << thongBao;
        getline(cin, s);
        s = catKhoangTrang(s);

        if (s == "") {
            cout << "Khong duoc de trong.\n";
            continue;
        }
        if (s.find('|') != string::npos) {
            cout << "Khong duoc nhap ky tu |.\n";
            continue;
        }

        return s;
    }
}

// Tach mot dong file text thanh cac truong theo ky tu '|', tra ve so truong tach duoc.
int tachDong(string dong, string truong[], int soTruongToiDa) {
    int soTruong = 0;
    string hienTai = "";

    for (int i = 0; i < (int)dong.length(); i++) {
        if (dong[i] == '|') {
            if (soTruong < soTruongToiDa) {
                truong[soTruong] = hienTai;
                soTruong++;
            }
            hienTai = "";
        } else {
            hienTai += dong[i];
        }
    }

    if (soTruong < soTruongToiDa) {
        truong[soTruong] = hienTai;
        soTruong++;
    }
    return soTruong;
}

// Lay thoi gian hien tai duoi dang chuoi yyyy-mm-dd hh:mm:ss de luu trong ket qua thi.
string layThoiGianHienTai() {
    time_t bayGio = time(NULL);
    tm* t = localtime(&bayGio);
    char boDem[32];
    strftime(boDem, sizeof(boDem), "%Y-%m-%d %H:%M:%S", t);
    return string(boDem);
}

// Tam dung man hinh console bang cach doi nguoi dung nhan Enter.
void tamDung() {
    cout << "\nNhan Enter de tiep tuc...";
    string s;
    getline(cin, s);
}

// Xao tron vector so nguyen bang Fisher-Yates; dung cho thu tu cau hoi va dap an.
void xaoTronVectorSoNguyen(vector<int>& a) {
    for (int i = static_cast<int>(a.size()) - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tam = a[i];
        a[i] = a[j];
        a[j] = tam;
    }
}

// Tinh diem theo thang 10; neu tong so cau khong hop le thi tra ve 0 de tranh chia cho 0.
double tinhDiem(int soCauDung, int tongSoCau) {
    if (tongSoCau <= 0) {
        return 0;
    }
    return (double)soCauDung * 10.0 / tongSoCau;
}
