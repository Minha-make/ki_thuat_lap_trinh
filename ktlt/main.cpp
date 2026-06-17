#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// ==================================================
// 1. KHAI BAO THU VIEN, HANG SO
// ==================================================

const int SO_DAP_AN = 4;
const int DO_DAI_DONG = 2048;
const char FILE_MON_HOC[] = "subjects.txt";
const char FILE_CAU_HOI[] = "questions.txt";
const char FILE_THI_SINH[] = "candidates.txt";
const char FILE_KET_QUA[] = "results.txt";

// ==================================================
// 2. KHAI BAO STRUCT DU LIEU
// ==================================================

struct MonHoc {
    int maMonHoc;
    string tenMonHoc;
};

struct CauHoi {
    int maCauHoi;
    int maMonHoc;
    int mucDo;
    string noiDung;
    string dapAn[SO_DAP_AN];
    int dapAnDung;
    bool dangHoatDong;
};

struct ThiSinh {
    int maThiSinh;
    string hoTen;
};

struct CauHoiThi {
    int maCauHoi;
    int thuTuDapAn[SO_DAP_AN];
    int dapAnDaChon;
};

struct KetQuaThi {
    int maKetQua;
    int maThiSinh;
    int maMonHoc;
    int tongSoCau;
    int soCauDung;
    double diem;
    string thoiGianBatDau;
    int thoiGianLamBaiGiay;
};

// ==================================================
// 3. TU CAI DAT MANG DONG
// ==================================================

template <class T>
struct MangDong {
    T* duLieu;
    int soLuong;
    int sucChua;
};

template <class T>
void khoiTaoMangDong(MangDong<T>& mang) {
    mang.sucChua = 8;
    mang.soLuong = 0;
    mang.duLieu = new T[mang.sucChua];
}

template <class T>
void giaiPhongMangDong(MangDong<T>& mang) {
    delete[] mang.duLieu;
    mang.duLieu = NULL;
    mang.soLuong = 0;
    mang.sucChua = 0;
}

template <class T>
void tangSucChuaMangDong(MangDong<T>& mang) {
    int sucChuaMoi = mang.sucChua * 2;
    T* duLieuMoi = new T[sucChuaMoi];

    for (int i = 0; i < mang.soLuong; i++) {
        duLieuMoi[i] = mang.duLieu[i];
    }

    delete[] mang.duLieu;
    mang.duLieu = duLieuMoi;
    mang.sucChua = sucChuaMoi;
}

template <class T>
void themVaoMangDong(MangDong<T>& mang, T giaTri) {
    if (mang.soLuong >= mang.sucChua) {
        tangSucChuaMangDong(mang);
    }
    mang.duLieu[mang.soLuong] = giaTri;
    mang.soLuong++;
}

template <class T>
void xoaTaiViTriMangDong(MangDong<T>& mang, int viTri) {
    if (viTri < 0 || viTri >= mang.soLuong) {
        return;
    }

    for (int i = viTri; i < mang.soLuong - 1; i++) {
        mang.duLieu[i] = mang.duLieu[i + 1];
    }
    mang.soLuong--;
}

template <class T>
void xoaTatCaMangDong(MangDong<T>& mang) {
    mang.soLuong = 0;
}

// ==================================================
// 4. KHAI BAO BIEN TOAN CUC
// ==================================================

MangDong<MonHoc> danhSachMonHoc;
MangDong<CauHoi> danhSachCauHoi;
MangDong<ThiSinh> danhSachThiSinh;
MangDong<KetQuaThi> danhSachKetQua;

// ==================================================
// 5. CAC HAM TIEN ICH
// ==================================================

string catKhoangTrang(string s) {
    int dau = 0;
    int cuoi = (int)s.length() - 1;

    while (dau <= cuoi && (s[dau] == ' ' || s[dau] == '\t' || s[dau] == '\r' || s[dau] == '\n')) {
        dau++;
    }

    while (cuoi >= dau && (s[cuoi] == ' ' || s[cuoi] == '\t' || s[cuoi] == '\r' || s[cuoi] == '\n')) {
        cuoi--;
    }

    if (dau > cuoi) {
        return "";
    }

    string ketQua = "";
    for (int i = dau; i <= cuoi; i++) {
        ketQua += s[i];
    }
    return ketQua;
}

bool laSoNguyen(string s) {
    s = catKhoangTrang(s);
    if (s == "") {
        return false;
    }

    int batDau = 0;
    if (s[0] == '-') {
        if (s.length() == 1) {
            return false;
        }
        batDau = 1;
    }

    for (int i = batDau; i < (int)s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}

bool chuoiChuaKyTu(string s, char kyTuCanTim) {
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] == kyTuCanTim) {
            return true;
        }
    }
    return false;
}

int chuyenChuoiThanhSo(string s) {
    int dau = 0;
    int dauAm = 1;
    int ketQua = 0;
    s = catKhoangTrang(s);

    if (s[0] == '-') {
        dauAm = -1;
        dau = 1;
    }

    for (int i = dau; i < (int)s.length(); i++) {
        ketQua = ketQua * 10 + (s[i] - '0');
    }
    return ketQua * dauAm;
}

double chuyenChuoiThanhSoThuc(string s) {
    double ketQua = 0;
    double heSoThapPhan = 0.1;
    bool sauDauCham = false;
    int dau = 0;
    int dauAm = 1;
    s = catKhoangTrang(s);

    if (s == "") {
        return 0;
    }

    if (s[0] == '-') {
        dauAm = -1;
        dau = 1;
    }

    for (int i = dau; i < (int)s.length(); i++) {
        if (s[i] == '.') {
            sauDauCham = true;
        } else if (s[i] >= '0' && s[i] <= '9') {
            if (!sauDauCham) {
                ketQua = ketQua * 10 + (s[i] - '0');
            } else {
                ketQua += (s[i] - '0') * heSoThapPhan;
                heSoThapPhan /= 10;
            }
        }
    }
    return ketQua * dauAm;
}

string chuyenBoolThanhChuoi(bool giaTri) {
    if (giaTri) {
        return "1";
    }
    return "0";
}

bool chuyenChuoiThanhBool(string s) {
    s = catKhoangTrang(s);
    return s == "1" || s == "true" || s == "TRUE";
}

int nhapSoNguyen(string thongBao, int giaTriNhoNhat, int giaTriLonNhat) {
    string dong;
    int giaTri;

    while (true) {
        cout << thongBao;
        getline(cin, dong);

        if (!laSoNguyen(dong)) {
            cout << "Du lieu khong hop le. Hay nhap so nguyen.\n";
            continue;
        }

        giaTri = chuyenChuoiThanhSo(dong);
        if (giaTri < giaTriNhoNhat || giaTri > giaTriLonNhat) {
            cout << "Gia tri phai nam trong khoang [" << giaTriNhoNhat << ", " << giaTriLonNhat << "].\n";
            continue;
        }

        return giaTri;
    }
}

string nhapChuoiKhongRong(string thongBao) {
    string giaTri;

    while (true) {
        cout << thongBao;
        getline(cin, giaTri);
        giaTri = catKhoangTrang(giaTri);

        if (giaTri == "") {
            cout << "Khong duoc de trong.\n";
            continue;
        }

        if (chuoiChuaKyTu(giaTri, '|')) {
            cout << "Khong duoc nhap ky tu | vi day la ky tu tach file.\n";
            continue;
        }

        return giaTri;
    }
}

void tamDung() {
    cout << "\nNhan Enter de tiep tuc...";
    string boDem;
    getline(cin, boDem);
}

int tachTruong(string dong, char kyTuTach, string truong[], int soTruongToiDa) {
    int soTruong = 0;
    string hienTai = "";

    for (int i = 0; i < (int)dong.length(); i++) {
        if (dong[i] == kyTuTach) {
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

string layThoiGianHienTai() {
    time_t bayGio = time(NULL);
    tm* thoiGian = localtime(&bayGio);
    char boDem[32];
    strftime(boDem, sizeof(boDem), "%Y-%m-%d %H:%M:%S", thoiGian);
    return string(boDem);
}

void xaoTronMangSoNguyen(int mang[], int soLuong) {
    for (int i = soLuong - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tam = mang[i];
        mang[i] = mang[j];
        mang[j] = tam;
    }
}

// ==================================================
// 6. KHOI TAO VA GIAI PHONG DU LIEU
// ==================================================

void khoiTaoTatCaDuLieu() {
    khoiTaoMangDong(danhSachMonHoc);
    khoiTaoMangDong(danhSachCauHoi);
    khoiTaoMangDong(danhSachThiSinh);
    khoiTaoMangDong(danhSachKetQua);
}

void giaiPhongTatCaDuLieu() {
    giaiPhongMangDong(danhSachMonHoc);
    giaiPhongMangDong(danhSachCauHoi);
    giaiPhongMangDong(danhSachThiSinh);
    giaiPhongMangDong(danhSachKetQua);
}

// ==================================================
// 7. MODULE DOC / GHI FILE
// ==================================================

void docDanhSachMonHocTuFile() {
    ifstream file(FILE_MON_HOC);
    string dong;
    string truong[2];
    xoaTatCaMangDong(danhSachMonHoc);

    if (!file.is_open()) {
        return;
    }

    while (getline(file, dong)) {
        dong = catKhoangTrang(dong);
        if (dong == "") {
            continue;
        }

        if (tachTruong(dong, '|', truong, 2) == 2 && laSoNguyen(truong[0])) {
            MonHoc monHoc;
            monHoc.maMonHoc = chuyenChuoiThanhSo(truong[0]);
            monHoc.tenMonHoc = truong[1];
            themVaoMangDong(danhSachMonHoc, monHoc);
        }
    }

    file.close();
}

void ghiDanhSachMonHocVaoFile() {
    ofstream file(FILE_MON_HOC);

    for (int i = 0; i < danhSachMonHoc.soLuong; i++) {
        file << danhSachMonHoc.duLieu[i].maMonHoc << "|"
             << danhSachMonHoc.duLieu[i].tenMonHoc << "\n";
    }

    file.close();
}

void docDanhSachCauHoiTuFile() {
    ifstream file(FILE_CAU_HOI);
    string dong;
    string truong[10];
    xoaTatCaMangDong(danhSachCauHoi);

    if (!file.is_open()) {
        return;
    }

    while (getline(file, dong)) {
        dong = catKhoangTrang(dong);
        if (dong == "") {
            continue;
        }

        if (tachTruong(dong, '|', truong, 10) == 10) {
            CauHoi cauHoi;
            cauHoi.maCauHoi = chuyenChuoiThanhSo(truong[0]);
            cauHoi.maMonHoc = chuyenChuoiThanhSo(truong[1]);
            cauHoi.mucDo = chuyenChuoiThanhSo(truong[2]);
            cauHoi.noiDung = truong[3];
            cauHoi.dapAn[0] = truong[4];
            cauHoi.dapAn[1] = truong[5];
            cauHoi.dapAn[2] = truong[6];
            cauHoi.dapAn[3] = truong[7];
            cauHoi.dapAnDung = chuyenChuoiThanhSo(truong[8]);
            cauHoi.dangHoatDong = chuyenChuoiThanhBool(truong[9]);
            themVaoMangDong(danhSachCauHoi, cauHoi);
        }
    }

    file.close();
}

void ghiDanhSachCauHoiVaoFile() {
    ofstream file(FILE_CAU_HOI);

    for (int i = 0; i < danhSachCauHoi.soLuong; i++) {
        CauHoi cauHoi = danhSachCauHoi.duLieu[i];
        file << cauHoi.maCauHoi << "|"
             << cauHoi.maMonHoc << "|"
             << cauHoi.mucDo << "|"
             << cauHoi.noiDung << "|"
             << cauHoi.dapAn[0] << "|"
             << cauHoi.dapAn[1] << "|"
             << cauHoi.dapAn[2] << "|"
             << cauHoi.dapAn[3] << "|"
             << cauHoi.dapAnDung << "|"
             << chuyenBoolThanhChuoi(cauHoi.dangHoatDong) << "\n";
    }

    file.close();
}

void docDanhSachThiSinhTuFile() {
    ifstream file(FILE_THI_SINH);
    string dong;
    string truong[2];
    xoaTatCaMangDong(danhSachThiSinh);

    if (!file.is_open()) {
        return;
    }

    while (getline(file, dong)) {
        dong = catKhoangTrang(dong);
        if (dong == "") {
            continue;
        }

        if (tachTruong(dong, '|', truong, 2) == 2 && laSoNguyen(truong[0])) {
            ThiSinh thiSinh;
            thiSinh.maThiSinh = chuyenChuoiThanhSo(truong[0]);
            thiSinh.hoTen = truong[1];
            themVaoMangDong(danhSachThiSinh, thiSinh);
        }
    }

    file.close();
}

void ghiDanhSachThiSinhVaoFile() {
    ofstream file(FILE_THI_SINH);

    for (int i = 0; i < danhSachThiSinh.soLuong; i++) {
        file << danhSachThiSinh.duLieu[i].maThiSinh << "|"
             << danhSachThiSinh.duLieu[i].hoTen << "\n";
    }

    file.close();
}

void docDanhSachKetQuaTuFile() {
    ifstream file(FILE_KET_QUA);
    string dong;
    string truong[8];
    xoaTatCaMangDong(danhSachKetQua);

    if (!file.is_open()) {
        return;
    }

    while (getline(file, dong)) {
        dong = catKhoangTrang(dong);
        if (dong == "") {
            continue;
        }

        if (tachTruong(dong, '|', truong, 8) == 8) {
            KetQuaThi ketQua;
            ketQua.maKetQua = chuyenChuoiThanhSo(truong[0]);
            ketQua.maThiSinh = chuyenChuoiThanhSo(truong[1]);
            ketQua.maMonHoc = chuyenChuoiThanhSo(truong[2]);
            ketQua.tongSoCau = chuyenChuoiThanhSo(truong[3]);
            ketQua.soCauDung = chuyenChuoiThanhSo(truong[4]);
            ketQua.diem = chuyenChuoiThanhSoThuc(truong[5]);
            ketQua.thoiGianBatDau = truong[6];
            ketQua.thoiGianLamBaiGiay = chuyenChuoiThanhSo(truong[7]);
            themVaoMangDong(danhSachKetQua, ketQua);
        }
    }

    file.close();
}

void ghiDanhSachKetQuaVaoFile() {
    ofstream file(FILE_KET_QUA);
    file << fixed << setprecision(2);

    for (int i = 0; i < danhSachKetQua.soLuong; i++) {
        KetQuaThi ketQua = danhSachKetQua.duLieu[i];
        file << ketQua.maKetQua << "|"
             << ketQua.maThiSinh << "|"
             << ketQua.maMonHoc << "|"
             << ketQua.tongSoCau << "|"
             << ketQua.soCauDung << "|"
             << ketQua.diem << "|"
             << ketQua.thoiGianBatDau << "|"
             << ketQua.thoiGianLamBaiGiay << "\n";
    }

    file.close();
}

void docTatCaDuLieuTuFile() {
    docDanhSachMonHocTuFile();
    docDanhSachCauHoiTuFile();
    docDanhSachThiSinhTuFile();
    docDanhSachKetQuaTuFile();
}

void ghiTatCaDuLieuVaoFile() {
    ghiDanhSachMonHocVaoFile();
    ghiDanhSachCauHoiVaoFile();
    ghiDanhSachThiSinhVaoFile();
    ghiDanhSachKetQuaVaoFile();
}

// ==================================================
// 8. MODULE QUAN LY MON HOC
// ==================================================

int timMonHocTheoMa(int maMonHoc) {
    for (int i = 0; i < danhSachMonHoc.soLuong; i++) {
        if (danhSachMonHoc.duLieu[i].maMonHoc == maMonHoc) {
            return i;
        }
    }
    return -1;
}

int sinhMaMonHocMoi() {
    int maLonNhat = 0;
    for (int i = 0; i < danhSachMonHoc.soLuong; i++) {
        if (danhSachMonHoc.duLieu[i].maMonHoc > maLonNhat) {
            maLonNhat = danhSachMonHoc.duLieu[i].maMonHoc;
        }
    }
    return maLonNhat + 1;
}

bool monHocDaDuocSuDung(int maMonHoc) {
    for (int i = 0; i < danhSachCauHoi.soLuong; i++) {
        if (danhSachCauHoi.duLieu[i].maMonHoc == maMonHoc) {
            return true;
        }
    }
    return false;
}

void hienThiDanhSachMonHoc() {
    cout << "\nDANH SACH MON HOC\n";
    cout << left << setw(10) << "Ma" << setw(40) << "Ten mon hoc" << "\n";
    cout << string(50, '-') << "\n";

    for (int i = 0; i < danhSachMonHoc.soLuong; i++) {
        cout << left << setw(10) << danhSachMonHoc.duLieu[i].maMonHoc
             << setw(40) << danhSachMonHoc.duLieu[i].tenMonHoc << "\n";
    }

    if (danhSachMonHoc.soLuong == 0) {
        cout << "Chua co mon hoc.\n";
    }
}

void themMonHoc() {
    MonHoc monHoc;
    monHoc.maMonHoc = sinhMaMonHocMoi();
    monHoc.tenMonHoc = nhapChuoiKhongRong("Nhap ten mon hoc: ");
    themVaoMangDong(danhSachMonHoc, monHoc);
    ghiDanhSachMonHocVaoFile();
    cout << "Da them mon hoc voi ma " << monHoc.maMonHoc << ".\n";
}

void suaMonHoc() {
    int maMonHoc = nhapSoNguyen("Nhap ma mon hoc can sua: ", 1, 1000000);
    int viTri = timMonHocTheoMa(maMonHoc);

    if (viTri == -1) {
        cout << "Khong tim thay mon hoc.\n";
        return;
    }

    danhSachMonHoc.duLieu[viTri].tenMonHoc = nhapChuoiKhongRong("Nhap ten mon hoc moi: ");
    ghiDanhSachMonHocVaoFile();
    cout << "Da sua mon hoc.\n";
}

void xoaMonHoc() {
    int maMonHoc = nhapSoNguyen("Nhap ma mon hoc can xoa: ", 1, 1000000);
    int viTri = timMonHocTheoMa(maMonHoc);

    if (viTri == -1) {
        cout << "Khong tim thay mon hoc.\n";
        return;
    }

    if (monHocDaDuocSuDung(maMonHoc)) {
        cout << "Khong the xoa vi mon hoc da co cau hoi.\n";
        return;
    }

    xoaTaiViTriMangDong(danhSachMonHoc, viTri);
    ghiDanhSachMonHocVaoFile();
    cout << "Da xoa mon hoc.\n";
}

void timKiemMonHoc() {
    int maMonHoc = nhapSoNguyen("Nhap ma mon hoc can tim: ", 1, 1000000);
    int viTri = timMonHocTheoMa(maMonHoc);

    if (viTri == -1) {
        cout << "Khong tim thay mon hoc.\n";
        return;
    }

    cout << "Ma: " << danhSachMonHoc.duLieu[viTri].maMonHoc << "\n";
    cout << "Ten: " << danhSachMonHoc.duLieu[viTri].tenMonHoc << "\n";
}

void menuQuanLyMonHoc() {
    while (true) {
        cout << "\n===== QUAN LY MON HOC =====\n";
        cout << "1. Them mon hoc\n";
        cout << "2. Hien thi danh sach mon hoc\n";
        cout << "3. Tim mon hoc theo ma\n";
        cout << "4. Sua ten mon hoc\n";
        cout << "5. Xoa mon hoc\n";
        cout << "0. Quay lai\n";

        int luaChon = nhapSoNguyen("Chon: ", 0, 5);
        if (luaChon == 0) return;
        if (luaChon == 1) themMonHoc();
        if (luaChon == 2) hienThiDanhSachMonHoc();
        if (luaChon == 3) timKiemMonHoc();
        if (luaChon == 4) suaMonHoc();
        if (luaChon == 5) xoaMonHoc();
        tamDung();
    }
}

// ==================================================
// 9. MODULE QUAN LY THI SINH
// ==================================================

int timThiSinhTheoMa(int maThiSinh) {
    for (int i = 0; i < danhSachThiSinh.soLuong; i++) {
        if (danhSachThiSinh.duLieu[i].maThiSinh == maThiSinh) {
            return i;
        }
    }
    return -1;
}

int sinhMaThiSinhMoi() {
    int maLonNhat = 0;
    for (int i = 0; i < danhSachThiSinh.soLuong; i++) {
        if (danhSachThiSinh.duLieu[i].maThiSinh > maLonNhat) {
            maLonNhat = danhSachThiSinh.duLieu[i].maThiSinh;
        }
    }
    return maLonNhat + 1;
}

bool thiSinhDaCoKetQua(int maThiSinh) {
    for (int i = 0; i < danhSachKetQua.soLuong; i++) {
        if (danhSachKetQua.duLieu[i].maThiSinh == maThiSinh) {
            return true;
        }
    }
    return false;
}

void hienThiDanhSachThiSinh() {
    cout << "\nDANH SACH THI SINH\n";
    cout << left << setw(10) << "Ma" << setw(40) << "Ho ten" << "\n";
    cout << string(50, '-') << "\n";

    for (int i = 0; i < danhSachThiSinh.soLuong; i++) {
        cout << left << setw(10) << danhSachThiSinh.duLieu[i].maThiSinh
             << setw(40) << danhSachThiSinh.duLieu[i].hoTen << "\n";
    }

    if (danhSachThiSinh.soLuong == 0) {
        cout << "Chua co thi sinh.\n";
    }
}

void themThiSinh() {
    ThiSinh thiSinh;
    thiSinh.maThiSinh = sinhMaThiSinhMoi();
    thiSinh.hoTen = nhapChuoiKhongRong("Nhap ho ten thi sinh: ");
    themVaoMangDong(danhSachThiSinh, thiSinh);
    ghiDanhSachThiSinhVaoFile();
    cout << "Da them thi sinh voi ma " << thiSinh.maThiSinh << ".\n";
}

void suaThiSinh() {
    int maThiSinh = nhapSoNguyen("Nhap ma thi sinh can sua: ", 1, 1000000);
    int viTri = timThiSinhTheoMa(maThiSinh);

    if (viTri == -1) {
        cout << "Khong tim thay thi sinh.\n";
        return;
    }

    danhSachThiSinh.duLieu[viTri].hoTen = nhapChuoiKhongRong("Nhap ho ten moi: ");
    ghiDanhSachThiSinhVaoFile();
    cout << "Da sua thi sinh.\n";
}

void xoaThiSinh() {
    int maThiSinh = nhapSoNguyen("Nhap ma thi sinh can xoa: ", 1, 1000000);
    int viTri = timThiSinhTheoMa(maThiSinh);

    if (viTri == -1) {
        cout << "Khong tim thay thi sinh.\n";
        return;
    }

    if (thiSinhDaCoKetQua(maThiSinh)) {
        cout << "Khong the xoa vi thi sinh da co ket qua thi.\n";
        return;
    }

    xoaTaiViTriMangDong(danhSachThiSinh, viTri);
    ghiDanhSachThiSinhVaoFile();
    cout << "Da xoa thi sinh.\n";
}

void timKiemThiSinh() {
    int maThiSinh = nhapSoNguyen("Nhap ma thi sinh can tim: ", 1, 1000000);
    int viTri = timThiSinhTheoMa(maThiSinh);

    if (viTri == -1) {
        cout << "Khong tim thay thi sinh.\n";
        return;
    }

    cout << "Ma: " << danhSachThiSinh.duLieu[viTri].maThiSinh << "\n";
    cout << "Ho ten: " << danhSachThiSinh.duLieu[viTri].hoTen << "\n";
}

void menuQuanLyThiSinh() {
    while (true) {
        cout << "\n===== QUAN LY THI SINH =====\n";
        cout << "1. Them thi sinh\n";
        cout << "2. Hien thi danh sach thi sinh\n";
        cout << "3. Tim thi sinh theo ma\n";
        cout << "4. Sua thi sinh\n";
        cout << "5. Xoa thi sinh\n";
        cout << "0. Quay lai\n";

        int luaChon = nhapSoNguyen("Chon: ", 0, 5);
        if (luaChon == 0) return;
        if (luaChon == 1) themThiSinh();
        if (luaChon == 2) hienThiDanhSachThiSinh();
        if (luaChon == 3) timKiemThiSinh();
        if (luaChon == 4) suaThiSinh();
        if (luaChon == 5) xoaThiSinh();
        tamDung();
    }
}

// ==================================================
// 10. MODULE QUAN LY NGAN HANG CAU HOI
// ==================================================

int timCauHoiTheoMa(int maCauHoi) {
    for (int i = 0; i < danhSachCauHoi.soLuong; i++) {
        if (danhSachCauHoi.duLieu[i].maCauHoi == maCauHoi) {
            return i;
        }
    }
    return -1;
}

int sinhMaCauHoiMoi() {
    int maLonNhat = 0;
    for (int i = 0; i < danhSachCauHoi.soLuong; i++) {
        if (danhSachCauHoi.duLieu[i].maCauHoi > maLonNhat) {
            maLonNhat = danhSachCauHoi.duLieu[i].maCauHoi;
        }
    }
    return maLonNhat + 1;
}

int demCauHoiDangHoatDongTheoMonHoc(int maMonHoc) {
    int dem = 0;
    for (int i = 0; i < danhSachCauHoi.soLuong; i++) {
        if (danhSachCauHoi.duLieu[i].maMonHoc == maMonHoc && danhSachCauHoi.duLieu[i].dangHoatDong) {
            dem++;
        }
    }
    return dem;
}

void hienThiMotCauHoi(CauHoi cauHoi) {
    cout << "\nMa cau hoi: " << cauHoi.maCauHoi << "\n";
    cout << "Ma mon hoc: " << cauHoi.maMonHoc << "\n";
    cout << "Muc do: " << cauHoi.mucDo << "\n";
    cout << "Noi dung: " << cauHoi.noiDung << "\n";
    cout << "A. " << cauHoi.dapAn[0] << "\n";
    cout << "B. " << cauHoi.dapAn[1] << "\n";
    cout << "C. " << cauHoi.dapAn[2] << "\n";
    cout << "D. " << cauHoi.dapAn[3] << "\n";
    cout << "Dap an dung: " << char('A' + cauHoi.dapAnDung) << "\n";
    cout << "Trang thai: " << (cauHoi.dangHoatDong ? "Dang hoat dong" : "Da xoa mem") << "\n";
}

void hienThiDanhSachCauHoi() {
    if (danhSachCauHoi.soLuong == 0) {
        cout << "Chua co cau hoi.\n";
        return;
    }

    for (int i = 0; i < danhSachCauHoi.soLuong; i++) {
        hienThiMotCauHoi(danhSachCauHoi.duLieu[i]);
    }
}

void hienThiDanhSachCauHoiDangHoatDong() {
    bool coDuLieu = false;

    for (int i = 0; i < danhSachCauHoi.soLuong; i++) {
        if (danhSachCauHoi.duLieu[i].dangHoatDong) {
            hienThiMotCauHoi(danhSachCauHoi.duLieu[i]);
            coDuLieu = true;
        }
    }

    if (!coDuLieu) {
        cout << "Chua co cau hoi dang hoat dong.\n";
    }
}

void nhapNoiDungCauHoi(CauHoi& cauHoi) {
    cauHoi.maMonHoc = nhapSoNguyen("Nhap ma mon hoc: ", 1, 1000000);
    while (timMonHocTheoMa(cauHoi.maMonHoc) == -1) {
        cout << "Ma mon hoc khong ton tai.\n";
        cauHoi.maMonHoc = nhapSoNguyen("Nhap lai ma mon hoc: ", 1, 1000000);
    }

    cauHoi.mucDo = nhapSoNguyen("Nhap muc do (1 de, 2 trung binh, 3 kho): ", 1, 3);
    cauHoi.noiDung = nhapChuoiKhongRong("Nhap noi dung cau hoi: ");
    cauHoi.dapAn[0] = nhapChuoiKhongRong("Nhap dap an A: ");
    cauHoi.dapAn[1] = nhapChuoiKhongRong("Nhap dap an B: ");
    cauHoi.dapAn[2] = nhapChuoiKhongRong("Nhap dap an C: ");
    cauHoi.dapAn[3] = nhapChuoiKhongRong("Nhap dap an D: ");
    cauHoi.dapAnDung = nhapSoNguyen("Nhap dap an dung (0=A, 1=B, 2=C, 3=D): ", 0, 3);
}

void themCauHoi() {
    if (danhSachMonHoc.soLuong == 0) {
        cout << "Can them mon hoc truoc khi them cau hoi.\n";
        return;
    }

    CauHoi cauHoi;
    cauHoi.maCauHoi = sinhMaCauHoiMoi();
    cauHoi.dangHoatDong = true;
    nhapNoiDungCauHoi(cauHoi);
    themVaoMangDong(danhSachCauHoi, cauHoi);
    ghiDanhSachCauHoiVaoFile();
    cout << "Da them cau hoi voi ma " << cauHoi.maCauHoi << ".\n";
}

void suaCauHoi() {
    int maCauHoi = nhapSoNguyen("Nhap ma cau hoi can sua: ", 1, 1000000);
    int viTri = timCauHoiTheoMa(maCauHoi);

    if (viTri == -1) {
        cout << "Khong tim thay cau hoi.\n";
        return;
    }

    nhapNoiDungCauHoi(danhSachCauHoi.duLieu[viTri]);
    ghiDanhSachCauHoiVaoFile();
    cout << "Da sua cau hoi.\n";
}

void xoaMemCauHoi() {
    int maCauHoi = nhapSoNguyen("Nhap ma cau hoi can xoa mem: ", 1, 1000000);
    int viTri = timCauHoiTheoMa(maCauHoi);

    if (viTri == -1) {
        cout << "Khong tim thay cau hoi.\n";
        return;
    }

    danhSachCauHoi.duLieu[viTri].dangHoatDong = false;
    ghiDanhSachCauHoiVaoFile();
    cout << "Da xoa mem cau hoi.\n";
}

void hienThiCauHoiTheoMonHoc() {
    int maMonHoc = nhapSoNguyen("Nhap ma mon hoc: ", 1, 1000000);
    bool coDuLieu = false;

    for (int i = 0; i < danhSachCauHoi.soLuong; i++) {
        if (danhSachCauHoi.duLieu[i].maMonHoc == maMonHoc) {
            hienThiMotCauHoi(danhSachCauHoi.duLieu[i]);
            coDuLieu = true;
        }
    }

    if (!coDuLieu) {
        cout << "Khong co cau hoi thuoc mon hoc nay.\n";
    }
}

void hienThiCauHoiTheoMucDo() {
    int mucDo = nhapSoNguyen("Nhap muc do (1, 2, 3): ", 1, 3);
    bool coDuLieu = false;

    for (int i = 0; i < danhSachCauHoi.soLuong; i++) {
        if (danhSachCauHoi.duLieu[i].mucDo == mucDo) {
            hienThiMotCauHoi(danhSachCauHoi.duLieu[i]);
            coDuLieu = true;
        }
    }

    if (!coDuLieu) {
        cout << "Khong co cau hoi voi muc do nay.\n";
    }
}

void menuQuanLyCauHoi() {
    while (true) {
        cout << "\n===== QUAN LY CAU HOI =====\n";
        cout << "1. Them cau hoi\n";
        cout << "2. Hien thi tat ca cau hoi\n";
        cout << "3. Hien thi cau hoi dang hoat dong\n";
        cout << "4. Sua cau hoi\n";
        cout << "5. Xoa mem cau hoi\n";
        cout << "6. Loc cau hoi theo mon hoc\n";
        cout << "7. Loc cau hoi theo muc do\n";
        cout << "0. Quay lai\n";

        int luaChon = nhapSoNguyen("Chon: ", 0, 7);
        if (luaChon == 0) return;
        if (luaChon == 1) themCauHoi();
        if (luaChon == 2) hienThiDanhSachCauHoi();
        if (luaChon == 3) hienThiDanhSachCauHoiDangHoatDong();
        if (luaChon == 4) suaCauHoi();
        if (luaChon == 5) xoaMemCauHoi();
        if (luaChon == 6) hienThiCauHoiTheoMonHoc();
        if (luaChon == 7) hienThiCauHoiTheoMucDo();
        tamDung();
    }
}

// ==================================================
// 11. MODULE SINH DE THI
// ==================================================

int thuThapChiSoCauHoiTheoMonHoc(int maMonHoc, int chiSoCauHoi[]) {
    int soLuong = 0;

    for (int i = 0; i < danhSachCauHoi.soLuong; i++) {
        if (danhSachCauHoi.duLieu[i].maMonHoc == maMonHoc && danhSachCauHoi.duLieu[i].dangHoatDong) {
            chiSoCauHoi[soLuong] = i;
            soLuong++;
        }
    }

    return soLuong;
}

void xaoTronDapAnChoCauHoiThi(CauHoiThi& cauHoiThi) {
    for (int i = 0; i < SO_DAP_AN; i++) {
        cauHoiThi.thuTuDapAn[i] = i;
    }
    xaoTronMangSoNguyen(cauHoiThi.thuTuDapAn, SO_DAP_AN);
}

void sinhDeThi(int maMonHoc, int soLuongCauHoi, MangDong<CauHoiThi>& deThi) {
    xoaTatCaMangDong(deThi);

    if (danhSachCauHoi.soLuong == 0) {
        return;
    }

    int* chiSoCauHoi = new int[danhSachCauHoi.soLuong];
    int soCauHopLe = thuThapChiSoCauHoiTheoMonHoc(maMonHoc, chiSoCauHoi);

    if (soCauHopLe < soLuongCauHoi) {
        delete[] chiSoCauHoi;
        return;
    }

    xaoTronMangSoNguyen(chiSoCauHoi, soCauHopLe);

    for (int i = 0; i < soLuongCauHoi; i++) {
        CauHoiThi cauHoiThi;
        cauHoiThi.maCauHoi = danhSachCauHoi.duLieu[chiSoCauHoi[i]].maCauHoi;
        cauHoiThi.dapAnDaChon = -1;
        xaoTronDapAnChoCauHoiThi(cauHoiThi);
        themVaoMangDong(deThi, cauHoiThi);
    }

    delete[] chiSoCauHoi;
}

// ==================================================
// 12. MODULE LAM BAI THI VA TINH GIO
// ==================================================

bool daHetGio(time_t thoiGianBatDau, int thoiGianLamBaiPhut) {
    time_t hienTai = time(NULL);
    double soGiayDaQua = difftime(hienTai, thoiGianBatDau);
    return soGiayDaQua >= thoiGianLamBaiPhut * 60;
}

void hienThiMotCauHoiThi(CauHoiThi cauHoiThi, int soThuTu) {
    int viTri = timCauHoiTheoMa(cauHoiThi.maCauHoi);

    if (viTri == -1) {
        cout << "Cau hoi khong ton tai.\n";
        return;
    }

    CauHoi cauHoi = danhSachCauHoi.duLieu[viTri];
    cout << "\nCau " << soThuTu << ": " << cauHoi.noiDung << "\n";
    for (int i = 0; i < SO_DAP_AN; i++) {
        int chiSoDapAnGoc = cauHoiThi.thuTuDapAn[i];
        cout << char('A' + i) << ". " << cauHoi.dapAn[chiSoDapAnGoc] << "\n";
    }
}

int nhapDapAnNguoiDung() {
    string dong;

    while (true) {
        cout << "Nhap dap an (A/B/C/D, bo trong de bo qua): ";
        getline(cin, dong);
        dong = catKhoangTrang(dong);

        if (dong == "") {
            return -1;
        }

        char kyTu = dong[0];
        if (kyTu >= 'a' && kyTu <= 'd') {
            kyTu = char(kyTu - 'a' + 'A');
        }

        if (kyTu >= 'A' && kyTu <= 'D') {
            return kyTu - 'A';
        }

        cout << "Dap an khong hop le.\n";
    }
}

void lamBaiThi(MangDong<CauHoiThi>& deThi, int thoiGianLamBaiPhut, int& thoiGianLamBaiGiay) {
    time_t thoiGianBatDau = time(NULL);

    for (int i = 0; i < deThi.soLuong; i++) {
        if (daHetGio(thoiGianBatDau, thoiGianLamBaiPhut)) {
            cout << "\nDa het gio. Bai thi ket thuc.\n";
            break;
        }

        hienThiMotCauHoiThi(deThi.duLieu[i], i + 1);
        int dapAnHienThi = nhapDapAnNguoiDung();

        if (dapAnHienThi >= 0) {
            deThi.duLieu[i].dapAnDaChon = deThi.duLieu[i].thuTuDapAn[dapAnHienThi];
        } else {
            deThi.duLieu[i].dapAnDaChon = -1;
        }

        if (daHetGio(thoiGianBatDau, thoiGianLamBaiPhut)) {
            cout << "\nDa het gio sau cau vua tra loi.\n";
            break;
        }
    }

    thoiGianLamBaiGiay = (int)difftime(time(NULL), thoiGianBatDau);
}

// ==================================================
// 13. MODULE CHAM DIEM
// ==================================================

int demSoCauDung(MangDong<CauHoiThi>& deThi) {
    int dem = 0;

    for (int i = 0; i < deThi.soLuong; i++) {
        int viTri = timCauHoiTheoMa(deThi.duLieu[i].maCauHoi);
        if (viTri != -1 && deThi.duLieu[i].dapAnDaChon == danhSachCauHoi.duLieu[viTri].dapAnDung) {
            dem++;
        }
    }

    return dem;
}

double tinhDiem(int soCauDung, int tongSoCau) {
    if (tongSoCau <= 0) {
        return 0;
    }
    return (double)soCauDung * 10.0 / tongSoCau;
}

int sinhMaKetQuaMoi() {
    int maLonNhat = 0;
    for (int i = 0; i < danhSachKetQua.soLuong; i++) {
        if (danhSachKetQua.duLieu[i].maKetQua > maLonNhat) {
            maLonNhat = danhSachKetQua.duLieu[i].maKetQua;
        }
    }
    return maLonNhat + 1;
}

KetQuaThi luuKetQuaThi(int maThiSinh, int maMonHoc, int tongSoCau, int soCauDung, double diem, int thoiGianLamBaiGiay) {
    KetQuaThi ketQua;
    ketQua.maKetQua = sinhMaKetQuaMoi();
    ketQua.maThiSinh = maThiSinh;
    ketQua.maMonHoc = maMonHoc;
    ketQua.tongSoCau = tongSoCau;
    ketQua.soCauDung = soCauDung;
    ketQua.diem = diem;
    ketQua.thoiGianBatDau = layThoiGianHienTai();
    ketQua.thoiGianLamBaiGiay = thoiGianLamBaiGiay;

    themVaoMangDong(danhSachKetQua, ketQua);
    ghiDanhSachKetQuaVaoFile();
    return ketQua;
}

void hienThiKetQuaSauThi(KetQuaThi ketQua) {
    cout << "\n===== KET QUA THI =====\n";
    cout << "Ma ket qua: " << ketQua.maKetQua << "\n";
    cout << "Ma thi sinh: " << ketQua.maThiSinh << "\n";
    cout << "Ma mon hoc: " << ketQua.maMonHoc << "\n";
    cout << "So cau dung: " << ketQua.soCauDung << "/" << ketQua.tongSoCau << "\n";
    cout << fixed << setprecision(2);
    cout << "Diem: " << ketQua.diem << "\n";
    cout << "Thoi gian lam bai: " << ketQua.thoiGianLamBaiGiay << " giay\n";
    cout << "Thoi gian ghi nhan: " << ketQua.thoiGianBatDau << "\n";
}

void batDauThi() {
    if (danhSachThiSinh.soLuong == 0 || danhSachMonHoc.soLuong == 0 || danhSachCauHoi.soLuong == 0) {
        cout << "Can co thi sinh, mon hoc va cau hoi truoc khi thi.\n";
        return;
    }

    hienThiDanhSachThiSinh();
    int maThiSinh = nhapSoNguyen("Nhap ma thi sinh: ", 1, 1000000);
    if (timThiSinhTheoMa(maThiSinh) == -1) {
        cout << "Thi sinh khong ton tai.\n";
        return;
    }

    hienThiDanhSachMonHoc();
    int maMonHoc = nhapSoNguyen("Nhap ma mon hoc: ", 1, 1000000);
    if (timMonHocTheoMa(maMonHoc) == -1) {
        cout << "Mon hoc khong ton tai.\n";
        return;
    }

    int soCauHopLe = demCauHoiDangHoatDongTheoMonHoc(maMonHoc);
    if (soCauHopLe == 0) {
        cout << "Mon hoc nay chua co cau hoi dang hoat dong.\n";
        return;
    }

    cout << "So cau hoi dang co: " << soCauHopLe << "\n";
    int soLuongCauHoi = nhapSoNguyen("Nhap so luong cau hoi: ", 1, soCauHopLe);
    int thoiGianLamBaiPhut = nhapSoNguyen("Nhap thoi gian lam bai (phut): ", 1, 300);

    MangDong<CauHoiThi> deThi;
    khoiTaoMangDong(deThi);
    sinhDeThi(maMonHoc, soLuongCauHoi, deThi);

    if (deThi.soLuong != soLuongCauHoi) {
        cout << "Khong the sinh de thi do ngan hang cau hoi khong du.\n";
        giaiPhongMangDong(deThi);
        return;
    }

    int thoiGianLamBaiGiay = 0;
    lamBaiThi(deThi, thoiGianLamBaiPhut, thoiGianLamBaiGiay);

    int soCauDung = demSoCauDung(deThi);
    double diem = tinhDiem(soCauDung, deThi.soLuong);
    KetQuaThi ketQua = luuKetQuaThi(maThiSinh, maMonHoc, deThi.soLuong, soCauDung, diem, thoiGianLamBaiGiay);
    hienThiKetQuaSauThi(ketQua);

    giaiPhongMangDong(deThi);
}

// ==================================================
// 14. MODULE BAO CAO KET QUA
// ==================================================

void hienThiMotKetQua(KetQuaThi ketQua) {
    cout << left
         << setw(8) << ketQua.maKetQua
         << setw(10) << ketQua.maThiSinh
         << setw(10) << ketQua.maMonHoc
         << setw(12) << ketQua.tongSoCau
         << setw(12) << ketQua.soCauDung
         << setw(10) << fixed << setprecision(2) << ketQua.diem
         << setw(22) << ketQua.thoiGianBatDau
         << setw(10) << ketQua.thoiGianLamBaiGiay << "\n";
}

void inTieuDeKetQua() {
    cout << left
         << setw(8) << "MaKQ"
         << setw(10) << "MaTS"
         << setw(10) << "MaMH"
         << setw(12) << "TongCau"
         << setw(12) << "Dung"
         << setw(10) << "Diem"
         << setw(22) << "Thoi gian"
         << setw(10) << "Giay" << "\n";
    cout << string(94, '-') << "\n";
}

void hienThiTatCaKetQua() {
    if (danhSachKetQua.soLuong == 0) {
        cout << "Chua co ket qua thi.\n";
        return;
    }

    inTieuDeKetQua();
    for (int i = 0; i < danhSachKetQua.soLuong; i++) {
        hienThiMotKetQua(danhSachKetQua.duLieu[i]);
    }
}

void hienThiKetQuaTheoThiSinh() {
    int maThiSinh = nhapSoNguyen("Nhap ma thi sinh: ", 1, 1000000);
    bool coDuLieu = false;
    inTieuDeKetQua();

    for (int i = 0; i < danhSachKetQua.soLuong; i++) {
        if (danhSachKetQua.duLieu[i].maThiSinh == maThiSinh) {
            hienThiMotKetQua(danhSachKetQua.duLieu[i]);
            coDuLieu = true;
        }
    }

    if (!coDuLieu) {
        cout << "Khong co ket qua cua thi sinh nay.\n";
    }
}

void hienThiKetQuaTheoMonHoc() {
    int maMonHoc = nhapSoNguyen("Nhap ma mon hoc: ", 1, 1000000);
    bool coDuLieu = false;
    inTieuDeKetQua();

    for (int i = 0; i < danhSachKetQua.soLuong; i++) {
        if (danhSachKetQua.duLieu[i].maMonHoc == maMonHoc) {
            hienThiMotKetQua(danhSachKetQua.duLieu[i]);
            coDuLieu = true;
        }
    }

    if (!coDuLieu) {
        cout << "Khong co ket qua cua mon hoc nay.\n";
    }
}

void sapXepKetQuaTheoDiemGiamDan() {
    for (int i = 0; i < danhSachKetQua.soLuong - 1; i++) {
        int viTriLonNhat = i;
        for (int j = i + 1; j < danhSachKetQua.soLuong; j++) {
            if (danhSachKetQua.duLieu[j].diem > danhSachKetQua.duLieu[viTriLonNhat].diem) {
                viTriLonNhat = j;
            }
        }

        if (viTriLonNhat != i) {
            KetQuaThi tam = danhSachKetQua.duLieu[i];
            danhSachKetQua.duLieu[i] = danhSachKetQua.duLieu[viTriLonNhat];
            danhSachKetQua.duLieu[viTriLonNhat] = tam;
        }
    }

    ghiDanhSachKetQuaVaoFile();
    cout << "Da sap xep ket qua theo diem giam dan.\n";
    hienThiTatCaKetQua();
}

void thongKeKetQuaThi() {
    if (danhSachKetQua.soLuong == 0) {
        cout << "Chua co ket qua de thong ke.\n";
        return;
    }

    double diemCaoNhat = danhSachKetQua.duLieu[0].diem;
    double diemThapNhat = danhSachKetQua.duLieu[0].diem;
    double tongDiem = 0;

    for (int i = 0; i < danhSachKetQua.soLuong; i++) {
        double diem = danhSachKetQua.duLieu[i].diem;
        if (diem > diemCaoNhat) {
            diemCaoNhat = diem;
        }
        if (diem < diemThapNhat) {
            diemThapNhat = diem;
        }
        tongDiem += diem;
    }

    cout << fixed << setprecision(2);
    cout << "So lan thi: " << danhSachKetQua.soLuong << "\n";
    cout << "Diem cao nhat: " << diemCaoNhat << "\n";
    cout << "Diem thap nhat: " << diemThapNhat << "\n";
    cout << "Diem trung binh: " << tongDiem / danhSachKetQua.soLuong << "\n";
}

void menuBaoCaoKetQua() {
    while (true) {
        cout << "\n===== BAO CAO KET QUA =====\n";
        cout << "1. Xem tat ca ket qua\n";
        cout << "2. Xem ket qua theo thi sinh\n";
        cout << "3. Xem ket qua theo mon hoc\n";
        cout << "4. Sap xep ket qua theo diem giam dan\n";
        cout << "5. Thong ke ket qua thi\n";
        cout << "0. Quay lai\n";

        int luaChon = nhapSoNguyen("Chon: ", 0, 5);
        if (luaChon == 0) return;
        if (luaChon == 1) hienThiTatCaKetQua();
        if (luaChon == 2) hienThiKetQuaTheoThiSinh();
        if (luaChon == 3) hienThiKetQuaTheoMonHoc();
        if (luaChon == 4) sapXepKetQuaTheoDiemGiamDan();
        if (luaChon == 5) thongKeKetQuaThi();
        tamDung();
    }
}

// ==================================================
// 15. MODULE KIEM THU
// ==================================================

void kiemThuMangDong() {
    MangDong<int> mang;
    khoiTaoMangDong(mang);

    for (int i = 1; i <= 20; i++) {
        themVaoMangDong(mang, i);
    }

    cout << "So luong sau khi them 20 phan tu: " << mang.soLuong << "\n";
    cout << "Suc chua hien tai: " << mang.sucChua << "\n";
    cout << "Cac gia tri: ";
    for (int i = 0; i < mang.soLuong; i++) {
        cout << mang.duLieu[i] << " ";
    }
    cout << "\n";

    xoaTaiViTriMangDong(mang, 5);
    cout << "Sau khi xoa vi tri 5: ";
    for (int i = 0; i < mang.soLuong; i++) {
        cout << mang.duLieu[i] << " ";
    }
    cout << "\n";

    giaiPhongMangDong(mang);
}

void kiemThuTinhDiem() {
    cout << "Tinh diem 8/10 = " << tinhDiem(8, 10) << "\n";
    cout << "Tinh diem 0/0 = " << tinhDiem(0, 0) << "\n";
}

void kiemThuXaoTron() {
    int mang[10];
    for (int i = 0; i < 10; i++) {
        mang[i] = i + 1;
    }

    xaoTronMangSoNguyen(mang, 10);
    cout << "Mang sau khi xao tron: ";
    for (int i = 0; i < 10; i++) {
        cout << mang[i] << " ";
    }
    cout << "\n";
}

void kiemThuTimKiem() {
    cout << "Tim mon hoc ma 1, vi tri = " << timMonHocTheoMa(1) << "\n";
    cout << "Tim thi sinh ma 1, vi tri = " << timThiSinhTheoMa(1) << "\n";
    cout << "Tim cau hoi ma 1, vi tri = " << timCauHoiTheoMa(1) << "\n";
}

void kiemThuDocGhiFile() {
    ghiTatCaDuLieuVaoFile();
    docTatCaDuLieuTuFile();
    cout << "Da ghi va doc lai tat ca file.\n";
    cout << "Mon hoc: " << danhSachMonHoc.soLuong << "\n";
    cout << "Cau hoi: " << danhSachCauHoi.soLuong << "\n";
    cout << "Thi sinh: " << danhSachThiSinh.soLuong << "\n";
    cout << "Ket qua: " << danhSachKetQua.soLuong << "\n";
}

void taoDuLieuMau() {
    xoaTatCaMangDong(danhSachMonHoc);
    xoaTatCaMangDong(danhSachCauHoi);
    xoaTatCaMangDong(danhSachThiSinh);
    xoaTatCaMangDong(danhSachKetQua);

    MonHoc mh1 = {1, "Ky thuat lap trinh"};
    MonHoc mh2 = {2, "Cau truc du lieu"};
    themVaoMangDong(danhSachMonHoc, mh1);
    themVaoMangDong(danhSachMonHoc, mh2);

    ThiSinh ts1 = {1, "Nguyen Van A"};
    ThiSinh ts2 = {2, "Tran Thi B"};
    themVaoMangDong(danhSachThiSinh, ts1);
    themVaoMangDong(danhSachThiSinh, ts2);

    CauHoi ch1;
    ch1.maCauHoi = 1;
    ch1.maMonHoc = 1;
    ch1.mucDo = 1;
    ch1.noiDung = "Vong lap nao kiem tra dieu kien truoc?";
    ch1.dapAn[0] = "while";
    ch1.dapAn[1] = "do while";
    ch1.dapAn[2] = "goto";
    ch1.dapAn[3] = "switch";
    ch1.dapAnDung = 0;
    ch1.dangHoatDong = true;
    themVaoMangDong(danhSachCauHoi, ch1);

    CauHoi ch2;
    ch2.maCauHoi = 2;
    ch2.maMonHoc = 1;
    ch2.mucDo = 2;
    ch2.noiDung = "Mang dong can thao tac nao de tranh ro ri bo nho?";
    ch2.dapAn[0] = "delete[]";
    ch2.dapAn[1] = "break";
    ch2.dapAn[2] = "continue";
    ch2.dapAn[3] = "return";
    ch2.dapAnDung = 0;
    ch2.dangHoatDong = true;
    themVaoMangDong(danhSachCauHoi, ch2);

    CauHoi ch3;
    ch3.maCauHoi = 3;
    ch3.maMonHoc = 1;
    ch3.mucDo = 2;
    ch3.noiDung = "Tim kiem tuyen tinh co do phuc tap nao trong truong hop xau?";
    ch3.dapAn[0] = "O(1)";
    ch3.dapAn[1] = "O(log n)";
    ch3.dapAn[2] = "O(n)";
    ch3.dapAn[3] = "O(n^2)";
    ch3.dapAnDung = 2;
    ch3.dangHoatDong = true;
    themVaoMangDong(danhSachCauHoi, ch3);

    CauHoi ch4;
    ch4.maCauHoi = 4;
    ch4.maMonHoc = 2;
    ch4.mucDo = 1;
    ch4.noiDung = "Ngan xep hoat dong theo nguyen tac nao?";
    ch4.dapAn[0] = "FIFO";
    ch4.dapAn[1] = "LIFO";
    ch4.dapAn[2] = "Random";
    ch4.dapAn[3] = "Tree";
    ch4.dapAnDung = 1;
    ch4.dangHoatDong = true;
    themVaoMangDong(danhSachCauHoi, ch4);

    ghiTatCaDuLieuVaoFile();
    cout << "Da tao du lieu mau va ghi vao 4 file text.\n";
}

void menuKiemThu() {
    while (true) {
        cout << "\n===== KIEM THU =====\n";
        cout << "1. Kiem thu mang dong\n";
        cout << "2. Kiem thu doc/ghi file\n";
        cout << "3. Kiem thu tinh diem\n";
        cout << "4. Kiem thu xao tron\n";
        cout << "5. Kiem thu tim kiem\n";
        cout << "6. Tao du lieu mau\n";
        cout << "0. Quay lai\n";

        int luaChon = nhapSoNguyen("Chon: ", 0, 6);
        if (luaChon == 0) return;
        if (luaChon == 1) kiemThuMangDong();
        if (luaChon == 2) kiemThuDocGhiFile();
        if (luaChon == 3) kiemThuTinhDiem();
        if (luaChon == 4) kiemThuXaoTron();
        if (luaChon == 5) kiemThuTimKiem();
        if (luaChon == 6) taoDuLieuMau();
        tamDung();
    }
}

// ==================================================
// 16. MENU CHUONG TRINH
// ==================================================

void hienThiMenuChinh() {
    cout << "\n========== CHUONG TRINH THI TRAC NGHIEM ==========\n";
    cout << "1. Quan ly mon hoc\n";
    cout << "2. Quan ly thi sinh\n";
    cout << "3. Quan ly ngan hang cau hoi\n";
    cout << "4. Bat dau thi\n";
    cout << "5. Bao cao ket qua\n";
    cout << "6. Kiem thu\n";
    cout << "0. Luu va thoat\n";
}

void chayMenuChinh() {
    while (true) {
        hienThiMenuChinh();
        int luaChon = nhapSoNguyen("Chon: ", 0, 6);

        if (luaChon == 0) {
            ghiTatCaDuLieuVaoFile();
            cout << "Da luu du lieu. Tam biet!\n";
            return;
        }

        if (luaChon == 1) menuQuanLyMonHoc();
        if (luaChon == 2) menuQuanLyThiSinh();
        if (luaChon == 3) menuQuanLyCauHoi();
        if (luaChon == 4) {
            batDauThi();
            tamDung();
        }
        if (luaChon == 5) menuBaoCaoKetQua();
        if (luaChon == 6) menuKiemThu();
    }
}

// ==================================================
// 17. HAM MAIN
// ==================================================

int main() {
    srand((unsigned int)time(NULL));
    khoiTaoTatCaDuLieu();
    docTatCaDuLieuTuFile();
    chayMenuChinh();
    giaiPhongTatCaDuLieu();
    return 0;
}
