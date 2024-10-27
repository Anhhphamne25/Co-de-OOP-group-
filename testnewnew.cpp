#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;

// Lớp cơ sở Nguoi
class Nguoi {
protected:
    string maso;
    float luong;

private:
    string hoten;

public:
    void nhap() {
        cout << endl
             << "Nhap ma so (bc: bienche / hd: hopdong): ";
        cin >> maso;
        cout << "Nhap ho ten: ";
        cin.ignore();
        getline(cin, hoten);
    }

    string getMaso() const { // Hàm getter cho maso
        return maso;
    }

    void in() const {
        cout << "Ma so: " << maso << endl
             << "Ho ten: " << hoten << endl
             << "Luong: " << luong << endl;
    }
};

// Lớp kế thừa Bienche
class Bienche : virtual public Nguoi {
private:
    double hsl; // Hệ số lương
    double pccv; // Phụ cấp chức vụ

public:
    void nhap() {
        cout << "Nhap he so luong (2.34, 2.67, ...): ";
        cin >> hsl;
        cout << "Nhap tien phu cap chuc vu: ";
        cin >> pccv;
        luong = hsl * 2400000 + pccv;
    }
};

// Lớp kế thừa Hopdong
class Hopdong : virtual public Nguoi {
private:
    float tcld; // Tiền công lao động
    float hsvg; // Hệ số vượt giờ
    int songaycong; // Số ngày công

public:
    void nhap() {
        cout << "Nhap tien cong lao dong: ";
        cin >> tcld;
        cout << "Nhap so ngay lam viec: ";
        cin >> songaycong;
        cout << "Nhap he so vuot gio: ";
        cin >> hsvg;
        luong = (songaycong <= 26) ? (songaycong * tcld) : ((songaycong + (songaycong - 26) * hsvg) * tcld);
    }
};

// Lớp Nhanvien
class NHANVIEN : public Bienche, public Hopdong {
    static int tsnv; // Tổng số nhân viên
    static float tsl; // Tổng số lương

public:
    NHANVIEN() {
        tsnv++;
    }

    ~NHANVIEN() {
        tsnv--;
        tsl -= luong;
    }

    void nhap() {
        Nguoi::nhap();
        if (maso[0] == 'b')
            Bienche::nhap();
        else
            Hopdong::nhap();
        tsl += luong;
    }

    static void ints() {
        cout << "Tong so nhan vien: " << tsnv << endl
             << "Tong so luong: " << tsl << endl;
    }

    NHANVIEN* next; // Móc liên kết
};
int NHANVIEN::tsnv = 0;
float NHANVIEN::tsl = 0.0;

// Lớp PHONGBAN
class PHONGBAN {
private:
    string tenPhong;
    vector<NHANVIEN*> danhSachNhanVien;

public:
    PHONGBAN(const string& ten) : tenPhong(ten) {}

    void themNhanVien(NHANVIEN* nv) {
        danhSachNhanVien.push_back(nv);
    }

    void hienThiDanhSach() const {
        cout << "Danh sach nhan vien trong " << tenPhong << ":\n";
        for (const auto& nv : danhSachNhanVien) {
            nv->in();
        }
    }

    string getTenPhong() const {
        return tenPhong;
    }
};

// Lớp DanhGia
class DanhGia {
private:
    int xepHang;
    string phanHoi;

public:
    DanhGia(int xepHang, const string& phanHoi)
        : xepHang(xepHang), phanHoi(phanHoi) {}

    void hienThiDanhGia() const {
        cout << "Xep hang: " << xepHang << "/10, Phan hoi: " << phanHoi << endl;
    }
};

// Chương trình chính
int main() {
    vector<PHONGBAN*> danhSachPhongBan;

    // Tạo phòng ban
    PHONGBAN* phongIT = new PHONGBAN("Phong IT");
    PHONGBAN* phongHR = new PHONGBAN("Phong Nhan Su");

    danhSachPhongBan.push_back(phongIT);
    danhSachPhongBan.push_back(phongHR);

    NHANVIEN* dau = nullptr;
    NHANVIEN* cuoi = nullptr;
    char tiep = 'c';

    while (tiep == 'c') {
        NHANVIEN* node = new NHANVIEN;
        node->nhap();
        node->next = nullptr;

        if (dau == nullptr) {
            dau = node;
            cuoi = node;
        } else {
            cuoi->next = node;
            cuoi = node;
        }

        // Thêm nhân viên vào phòng ban tương ứng
       if (!node->getMaso().empty() && node->getMaso()[0] == 'b') {
    phongIT->themNhanVien(node);
} else {
    phongHR->themNhanVien(node);
}

        cout << "Nhap c de nhap tiep: ";
        cin >> tiep;
    }

    // Hiển thị thông tin nhân viên trong các phòng ban
    for (const auto& pb : danhSachPhongBan) {
        pb->hienThiDanhSach();
    }

    // Hiển thị tổng số nhân viên và tổng số lương
    NHANVIEN::ints();

    // Dọn dẹp bộ nhớ
    for (const auto& nv : danhSachPhongBan) {
        delete nv;
    }

    return 0;
}
