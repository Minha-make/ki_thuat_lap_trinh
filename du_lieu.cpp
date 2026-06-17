#include "du_lieu.h"

const char FILE_MON_HOC[] = "subjects.txt";
const char FILE_CAU_HOI[] = "questions.txt";
const char FILE_THI_SINH[] = "candidates.txt";
const char FILE_KET_QUA[] = "results.txt";

vector<MonHoc> dsMonHoc;
vector<CauHoi> dsCauHoi;
vector<ThiSinh> dsThiSinh;
vector<KetQuaThi> dsKetQua;
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

// Kiem tra mot chuoi co phai so nguyen khong am hay khong.
bool laSoNguyen(string s) {
    s = catKhoangTrang(s);
    if (s == "") return false;

    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

// Chuyen chuoi dang so thanh double, dung duoc cho ca so nguyen va so thuc.
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

// Nhap so nguyen trong khoang cho phep va phong ngua nhap sai.
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

// Nhap chuoi khong rong va khong chua ky tu phan tach file.
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

// Tach mot dong file text thanh cac truong theo ky tu '|'.
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

// Lay thoi gian hien tai duoi dang chuoi de luu ket qua thi.
string layThoiGianHienTai() {
    time_t bayGio = time(NULL);
    tm* t = localtime(&bayGio);
    char boDem[32];
    strftime(boDem, sizeof(boDem), "%Y-%m-%d %H:%M:%S", t);
    return string(boDem);
}

// Tam dung man hinh console cho nguoi dung doc ket qua.
void tamDung() {
    cout << "\nNhan Enter de tiep tuc...";
    string s;
    getline(cin, s);
}

// Xao tron vector so nguyen bang thuat toan Fisher-Yates.
void xaoTronVectorSoNguyen(vector<int>& a) {
    for (int i = static_cast<int>(a.size()) - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tam = a[i];
        a[i] = a[j];
        a[j] = tam;
    }
}

// Tinh diem theo thang 10 tu so cau dung va tong so cau.
double tinhDiem(int soCauDung, int tongSoCau) {
    if (tongSoCau <= 0) {
        return 0;
    }
    return (double)soCauDung * 10.0 / tongSoCau;
}

// ==================================================
// 6. DOC VA GHI FILE
// ==================================================

// Doc tat ca du lieu tu 4 file text vao bo nho.
void docDuLieu() {
    ifstream file;
    string dong;
    string t[10];

    dsMonHoc.clear();
    dsCauHoi.clear();
    dsThiSinh.clear();
    dsKetQua.clear();

    file.open(FILE_MON_HOC);
    while (getline(file, dong)) {
        if (tachDong(dong, t, 2) == 2 && laSoNguyen(t[0])) {
            MonHoc mh;
            mh.maMonHoc = static_cast<int>(chuoiSangSo(t[0]));
            mh.tenMonHoc = t[1];
            dsMonHoc.push_back(mh);
        }
    }
    file.close();

    file.open(FILE_CAU_HOI);
    while (getline(file, dong)) {
        // questions.txt gom 9 truong, khong luu trang thai cau hoi vi khong co xoa mem.
        if (tachDong(dong, t, 9) == 9 && laSoNguyen(t[0])) {
            CauHoi ch;
            ch.maCauHoi = static_cast<int>(chuoiSangSo(t[0]));
            ch.maMonHoc = static_cast<int>(chuoiSangSo(t[1]));
            ch.mucDo = static_cast<int>(chuoiSangSo(t[2]));
            ch.noiDung = t[3];
            ch.dapAn[0] = t[4];
            ch.dapAn[1] = t[5];
            ch.dapAn[2] = t[6];
            ch.dapAn[3] = t[7];
            ch.dapAnDung = static_cast<int>(chuoiSangSo(t[8]));
            dsCauHoi.push_back(ch);
        }
    }
    file.close();

    file.open(FILE_THI_SINH);
    while (getline(file, dong)) {
        if (tachDong(dong, t, 2) == 2 && laSoNguyen(t[0])) {
            ThiSinh ts;
            ts.maThiSinh = static_cast<int>(chuoiSangSo(t[0]));
            ts.hoTen = t[1];
            dsThiSinh.push_back(ts);
        }
    }
    file.close();

    file.open(FILE_KET_QUA);
    while (getline(file, dong)) {
        // results.txt gom 7 truong, khong luu diem vi diem tinh duoc tu so cau dung va tong so cau.
        if (tachDong(dong, t, 7) == 7 && laSoNguyen(t[0])) {
            KetQuaThi kq;
            kq.maKetQua = static_cast<int>(chuoiSangSo(t[0]));
            kq.maThiSinh = static_cast<int>(chuoiSangSo(t[1]));
            kq.maMonHoc = static_cast<int>(chuoiSangSo(t[2]));
            kq.tongSoCau = static_cast<int>(chuoiSangSo(t[3]));
            kq.soCauDung = static_cast<int>(chuoiSangSo(t[4]));
            kq.thoiGianThi = t[5];
            kq.thoiGianLamBaiGiay = static_cast<int>(chuoiSangSo(t[6]));
            dsKetQua.push_back(kq);
        }
    }
    file.close();
}

// Ghi toan bo du lieu hien tai ra 4 file text.
void ghiDuLieu() {
    ofstream file;

    file.open(FILE_MON_HOC);
    for (int i = 0; i < static_cast<int>(dsMonHoc.size()); i++) {
        file << dsMonHoc[i].maMonHoc << "|" << dsMonHoc[i].tenMonHoc << "\n";
    }
    file.close();

    file.open(FILE_CAU_HOI);
    for (int i = 0; i < static_cast<int>(dsCauHoi.size()); i++) {
        CauHoi ch = dsCauHoi[i];
        file << ch.maCauHoi << "|" << ch.maMonHoc << "|" << ch.mucDo << "|"
             << ch.noiDung << "|" << ch.dapAn[0] << "|" << ch.dapAn[1] << "|"
             << ch.dapAn[2] << "|" << ch.dapAn[3] << "|" << ch.dapAnDung << "\n";
    }
    file.close();

    file.open(FILE_THI_SINH);
    for (int i = 0; i < static_cast<int>(dsThiSinh.size()); i++) {
        file << dsThiSinh[i].maThiSinh << "|" << dsThiSinh[i].hoTen << "\n";
    }
    file.close();

    file.open(FILE_KET_QUA);
    for (int i = 0; i < static_cast<int>(dsKetQua.size()); i++) {
        KetQuaThi kq = dsKetQua[i];
        file << kq.maKetQua << "|" << kq.maThiSinh << "|" << kq.maMonHoc << "|"
             << kq.tongSoCau << "|" << kq.soCauDung << "|"
             << kq.thoiGianThi << "|" << kq.thoiGianLamBaiGiay << "\n";
    }
    file.close();
}

// ==================================================
// 7. QUAN LY NGAN HANG CAU HOI
// ==================================================

// Tim vi tri mon hoc theo ma mon hoc.
int timMonHoc(int maMonHoc) {
    for (int i = 0; i < static_cast<int>(dsMonHoc.size()); i++) {
        if (dsMonHoc[i].maMonHoc == maMonHoc) return i;
    }
    return -1;
}

// Tim vi tri thi sinh theo ma thi sinh.
int timThiSinh(int maThiSinh) {
    for (int i = 0; i < static_cast<int>(dsThiSinh.size()); i++) {
        if (dsThiSinh[i].maThiSinh == maThiSinh) return i;
    }
    return -1;
}

// Tim vi tri cau hoi theo ma cau hoi.
int timCauHoi(int maCauHoi) {
    for (int i = 0; i < static_cast<int>(dsCauHoi.size()); i++) {
        if (dsCauHoi[i].maCauHoi == maCauHoi) return i;
    }
    return -1;
}


