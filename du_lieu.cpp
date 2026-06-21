#include "du_lieu.h"

// Ten file text duoc khai bao extern trong du_lieu.h va dinh nghia tai day.
const char FILE_MON_HOC[] = "data/subjects.txt";
const char FILE_CAU_HOI[] = "data/questions.txt";
const char FILE_THI_SINH[] = "data/candidates.txt";
const char FILE_KET_QUA[] = "data/results.txt";

// Cac vector nay la bo nho chinh cua chuong trinh sau khi doc file.
vector<MonHoc> dsMonHoc;
vector<CauHoi> dsCauHoi;
vector<ThiSinh> dsThiSinh;
vector<KetQuaThi> dsKetQua;

// Doc tat ca du lieu tu 4 file text vao cac vector, moi dong file la mot ban ghi.
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

// Ghi toan bo du lieu hien tai trong vector ra 4 file text theo dung dinh dang da thong nhat.
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

// Tim vi tri mon hoc theo ma; tra ve -1 neu khong tim thay.
int timMonHoc(int maMonHoc) {
    for (int i = 0; i < static_cast<int>(dsMonHoc.size()); i++) {
        if (dsMonHoc[i].maMonHoc == maMonHoc) return i;
    }
    return -1;
}

// Tim vi tri thi sinh theo ma; tra ve -1 neu khong tim thay.
int timThiSinh(int maThiSinh) {
    for (int i = 0; i < static_cast<int>(dsThiSinh.size()); i++) {
        if (dsThiSinh[i].maThiSinh == maThiSinh) return i;
    }
    return -1;
}

// Tim vi tri cau hoi theo ma; tra ve -1 neu khong tim thay.
int timCauHoi(int maCauHoi) {
    for (int i = 0; i < static_cast<int>(dsCauHoi.size()); i++) {
        if (dsCauHoi[i].maCauHoi == maCauHoi) return i;
    }
    return -1;
}
