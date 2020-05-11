#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <set>
#include <map>
#include <bitset>
#include <cmath>
#include <complex>
#include <array>
#include <cassert>
#include <functional>

using namespace std;

#define REP(i,n) for(ll (i) = (0);(i) < (n);++i)
#define REV(i,n) for(ll (i) = (n) - 1;(i) >= 0;--i)
#define PB push_back
#define EB emplace_back
#define MP make_pair
#define FI first
#define SE second
#define SHOW1d(v,n) {REP(WW,n)cerr << v[WW] << ' ';cerr << endl << endl;}
#define SHOW2d(v,WW,HH) {REP(W_,WW){REP(H_,HH)cerr << v[W_][H_] << ' ';cerr << endl;}cerr << endl;}
#define ALL(v) v.begin(),v.end()
#define Decimal fixed<<setprecision(20)
#define INF 1000000000
#define LLINF 1000000000000000000LL
#define MOD 998244353

typedef long long ll;
typedef pair<ll,ll> P;
//--------geometry original ------------------
#define curr(PP, i) PP[i]
#define next(PP, i) PP[(i+1)%PP.size()]
#define diff(PP, i) (next(PP, i) - curr(PP, i))
#define eq(n,m) (abs((n)-(m)) < EPS)

typedef long long ll;
typedef pair<ll, ll> P;

const double EPS = 1e-8;
const double EPS_GIG = 1e-3;
const double PI = acos(-1.0);

struct point {
	double x, y;
	point(double x_, double y_):x(x_), y(y_){};
	point(const point &p):x(p.x), y(p.y){}
	point():x(0), y(0){}
	point& operator+=(point a){x += a.x;y += a.y;return *this;}
	point& operator-=(point a){x -= a.x;y -= a.y;return *this;}
	point& operator*=(point a){
		double xx = x * a.x - y * a.y;
		double yy = x * a.y + y * a.x;
		x = xx;y = yy;return *this;
	}
	point& operator*=(double a){x *= a;y *= a;return *this;}
	point& operator/=(double a){x /= a;y /= a;return *this;}
	point operator+(point a) const{return point(x, y)+=a;}
	point operator-(point a) const{return point(x, y)-=a;}
	point operator-() const{return point(-x, -y);}
	point operator*(point a) const{return point(x, y)*=a;}
	point operator*(double a) const{return point(x, y)*=a;}
	point operator/(double a) const{return point(x, y)/=a;}
	bool operator<(point a) const{return (x != a.x ? x < a.x : y < a.y);}
	double real() {return x;}
	double imag() {return y;}
};

template <class T>
point operator*(const T a, const point p){return p * a;}

point conj(point p) {return point(p.x, -p.y);}
double arg(point p) {return arg(complex<double>(p.x, p.y));}
double abs(point p) {return abs(complex<double>(p.x, p.y));}
double norm(point p) {return norm(complex<double>(p.x, p.y));}
double real(point p) {return p.x;}
double imag(point p) {return p.y;}

struct circle {
	point p; double r;
	circle(){}
	circle(const point &p, double r) : p(p), r(r) { }
};

// 扇型、中心と半径、二つの端点
// 現在中心角が180未満の前提
struct sector {
	point o;
	point a, b;
	double r;
	sector(){}
	sector(point O, point A, point B, double _r) :o(O), a(A), b(B), r(_r) {}
};

struct segment : public array<point, 2> {
	segment(const point &a, const point &b) {
		at(0) = a;
		at(1) = b;
	}
};

double cross(const point& a, const point& b) {
	return (conj(a)*b).y;
}

double dot(const point& a, const point& b) {
	return (conj(a)*b).x;
}

//角度足し算
double add_rad(double a,double b){
	double ret = a + b;
	if(ret > 2 * PI)ret -= 2 * PI;
	return ret;
}

//なす角(vector)
double angle(const point &a,const point &b) {
	auto tmp = abs(arg(a) - arg(b));
	return min(tmp, 2 * PI - tmp);
}

double angle(const segment &s1,const segment &s2) {
	return angle(s1[1] - s1[0], s2[1] - s2[0]);
}

//点の回転
point rotate(const point &p, double rad) {
	double x = p.x * cos(rad) - p.y * sin(rad);
	double y = p.y * cos(rad) + p.x * sin(rad);
	return point(x, y);
}

//並行
bool isParallel(const point &a, const point &b){
    return abs(cross(a,b)) < EPS;
}
bool isParallel(const segment &a, const segment &b){
    return isParallel(a[1]-a[0], b[1]-b[0]);
}
//直行
bool isOrthogonal(const point &a,const point &b){
	return abs(angle(a,b) - PI / 2) < EPS;
}
bool isOrthogonal(const segment &a,const segment &b){
	return isOrthogonal(a[1]-a[0],b[1]-b[0]);
}

/*
a → b で時計方向に折れて b → c
a → b で半時計方向に折れて b → c
a → b で逆を向いて a を通り越して b → c
a → b でそのまま b → c
a → b で逆を向いて b → c ( または b == c )
*/

int ccw(point a, point b, point c) {
	b -= a; c -= a;
	if (cross(b, c) > EPS)   return +1;       // counter clockwise
	if (cross(b, c) + EPS < 0)   return -1;       // clockwise
	if (dot(b, c) < 0)     return +2;       // c--a--b on line
	if (norm(b) < norm(c)) return -2;       // a--b--c on line
	return 0;
}

bool intersectLL(const segment &l, const segment &m) {
	return abs(cross(l[1] - l[0], m[1] - m[0])) > EPS || // non-parallel
		abs(cross(l[1] - l[0], m[0] - l[0])) < EPS;   // same line
}
bool intersectLS(const segment &l, const segment &s) {
	return cross(l[1] - l[0], s[0] - l[0])*       // s[0] is left of l
		cross(l[1] - l[0], s[1] - l[0]) < EPS; // s[1] is right of l
}
bool intersectLP(const segment &l, const point &p) {
	return abs(cross(l[1] - p, l[0] - p)) < EPS;
}
bool intersectSP(const segment &s, const point &p) {
	auto a = s[0] - p;
	auto b = s[1] - p;
	return (abs(cross(a, b)) < EPS && dot(a, b) <= EPS); // triangle inequality
}
//端点の交差も考える
bool intersectSS(const segment &s, const segment &t) {
	return ccw(s[0], s[1], t[0]) * ccw(s[0], s[1], t[1]) <= 0 &&
		ccw(t[0], t[1], s[0]) * ccw(t[0], t[1], s[1]) <= 0;
}
//端点の交差hは考えない
bool strictIntersectSS(const segment &s, const segment &t) {
	return ccw(s[0], s[1], t[0]) * ccw(s[0], s[1], t[1]) == -1 &&
		ccw(t[0], t[1], s[0]) * ccw(t[0], t[1], s[1]) == -1;
}

point projection(const segment &l, const point &p) {
	double t = dot(p - l[0], l[0] - l[1]) / norm(l[0] - l[1]);
	return l[0] + t*(l[0] - l[1]);
}
point reflection(const segment &l, const point &p) {
	return p + 2. * (projection(l, p) - p);
}
double distanceLP(const segment &l, const point &p) {
	return abs(p - projection(l, p));
}
double distanceLL(const segment &l, const segment &m) {
	return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}
double distanceLS(const segment &l, const segment &s) {
	if (intersectLS(l, s)) return 0;
	return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}
double distanceSP(const segment &s, const point &p) {
	const point r = projection(s, p);
	if (intersectSP(s, r)) return abs(r - p);
	return min(abs(s[0] - p), abs(s[1] - p));
}
double distanceSS(const segment &s, const segment &t) {
	if (intersectSS(s, t)) return 0;
	return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
		min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}
double distancePP(const point &a,const point &b){
	return abs(a-b);
}

/*多角形内包判定
half-line crossing method
OUT:0
ON:1
IN:2
*/
int contains(const vector<point>& Poly, const point& p) {
	bool in = false;
	for (int i = 0; i < Poly.size(); ++i) {
		point a = curr(Poly, i) - p, b = next(Poly, i) - p;
		if (a.y > b.y) swap(a, b);
		if (a.y < EPS && EPS < b.y && cross(a, b) > EPS)in = !in;
		if (abs(cross(a, b)) < EPS && dot(a, b) < EPS) return 1;
	}
	return in ? 2 : 0;
}

/*
OUT:0
ON:1
IN:2
*/
int contain_sector(const sector &sec, point &p){
	if(eq(abs(p - sec.o), sec.r))return 1;
	if(intersectSP(segment(sec.o, sec.a), p))return 1;
	if(intersectSP(segment(sec.o, sec.b), p))return 1;
	if(abs(p - sec.o) + EPS > sec.r)return 0;
	point vec = p - sec.o;
	point vecA = sec.a - sec.o;
	point vecB = sec.b - sec.o;
	if(angle(vec, vecA) + EPS < angle(vecA, vecB) && angle(vec, vecB) + EPS < angle(vecA, vecB))return 2;
	return 0;
}

//交点
point crosspointSS(const segment &l, const segment &m) {
	double A = cross(l[1] - l[0], m[1] - m[0]);
	double B = cross(l[1] - l[0], l[1] - m[0]);
	if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
	if (abs(A) < EPS) return point(INF,INF); // !!!PRECONDITION NOT SATISFIED!!!
	return m[0] + B / A * (m[1] - m[0]);
}

vector<point> crosspointCL(const circle &c, const segment &l) {
	auto ret = vector<point>(2, point(INF, INF));
	auto pro_p = projection(l, c.p);
	auto dist = distanceLP(l, c.p);
	if(abs(dist - c.r) < EPS){
		ret[0] = pro_p;
		return ret;
	}
	if(c.r < dist){
		return ret;
	}
	point vec = (l[1] - l[0]) * sqrt(c.r * c.r - dist * dist) / abs(l[1] - l[0]);
	ret[0] = pro_p + vec;
	ret[1] = pro_p - vec;
	return ret;
}

vector<point> crosspointCC(const circle c1, const circle c2) {
	auto ret = vector<point>(2, point(INF, INF));
	auto dist = abs(c2.p - c1.p);
	if(eq(dist, c1.r + c2.r) || eq(dist, abs(c2.r - c1.r))){
		auto tmp = c2.p - c1.p;
		ret[0] = c1.p + tmp * (c1.r / dist);
		return ret;
	}
	if(c1.r + c2.r < dist || dist < abs(c1.r - c2.r)){
		return ret;
	}
	auto alpha = acos((c1.r * c1.r + dist * dist - c2.r * c2.r) / (2 * c1.r * dist));
	auto theta = atan2(c2.p.y - c1.p.y, c2.p.x - c1.p.x);
	ret[0] = c1.p + point(cos(theta + alpha) * c1.r, sin(theta + alpha) * c1.r);
	ret[1] = c1.p + point(cos(theta - alpha) * c1.r, sin(theta - alpha) * c1.r);
	return ret;
}

bool isOnSector(const sector sec, const point p) {
	point vec = p - sec.o;
	point vecA = sec.a - sec.o;
	point vecB = sec.b - sec.o;
	if(eq(angle(vec, vecA) + angle(vec, vecB), angle(vecA, vecB)))return true;
	return false;
}

vector<point> crosspointSecS(const sector sec, const segment s) {
	circle c = circle(sec.o, sec.r);
	auto ret = crosspointCL(c, s);
	point inf = point(INF, INF);
	REP(i, 2){
		if(eq(ret[i], inf))continue;
		if(!isOnSector(sec, ret[i])){
			ret[i] = inf;
			continue;
		}
		if(!intersectSP(s, ret[i])){
			ret[i] = inf;
		}
	}
	return ret;
}
vector<point> crosspointSecSec(const sector sec1, const sector sec2) {
	circle c1 = circle(sec1.o, sec1.r);
	circle c2 = circle(sec2.o, sec2.r);
	auto ret = crosspointCC(c1, c2);
	point inf = point(INF, INF);
	REP(i, 2){
		if(!isOnSector(sec1, ret[i])){
			ret[i] = inf;
			continue;
		}
		if(!isOnSector(sec2, ret[i])){
			ret[i] = inf;
		}
	}
	return ret;
}


//凸包
vector<point> convex_hull(vector<point> ps) {
	int n = ps.size(), k = 0;
	sort(ps.begin(), ps.end());
	vector<point> ch(2*n);
	for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
		while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) == -1) --k;
	for (int i = n-2, t = k+1;i >= 0; ch[k++] = ps[i--]) // upper-hull
		while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) == -1) --k;
	ch.resize(k - 1);
	return ch;
}

//見えるか(可視グラフ用)
bool block_off(const point &a, const point &b, const vector<point> &obj) {
  point m = (a + b) * 0.5;
  bool on = false, in = false;
  for (int j = 0; j < obj.size(); ++j) {
    point c = curr(obj,j), d = next(obj,j);
    if (d.y < c.y) swap(c, d);
    if (cross(a-c,b-c) * cross(a-d,b-d) < 0 &&    // strictly intersect.
        cross(c-a,d-a) * cross(c-b,d-b) < 0) return true;
    if (cross(a-c,b-c) == 0 && dot(a-c,b-c) < 0) return true;
    if (c.y <= m.y && m.y < d.y)  // strictly contain.
      if (cross(c-m,d-m) < 0) in = !in;
    if (cross(c-m,d-m) == 0 && dot(c-m,d-m) <= EPS) on = true;
  }
  return !on && in;
}

//面積
double area(const vector<point>& p) {
	double A = 0;
	for (int i = 0; i < p.size(); ++i)
		A += cross(curr(p, i), next(p, i));
	return A / 2.;
}

//凸包判定
bool isConvex(vector<point> poly){
	int sz = poly.size();
	REP(i,sz){
		if(ccw(poly[i],poly[(i+1)%sz],poly[(i+2)%sz]) == -1)return false;
	}
	return true;
}

double convex_diameter(const vector<point> &pt) {
  const int n = pt.size();
  int is = 0, js = 0;
  for (int i = 1; i < n; ++i) {
    if (pt[i].y > pt[is].y) is = i;
    if (pt[i].y < pt[js].y) js = i;
  }
  double maxd = norm(pt[is]-pt[js]);

  int i, maxi, j, maxj;
  i = maxi = is;
  j = maxj = js;
  do {
    if (cross(diff(pt,i), diff(pt,j)) >= 0) j = (j+1) % n;
    else i = (i+1) % n;
    if (norm(pt[i]-pt[j]) > maxd) {
      maxd = norm(pt[i]-pt[j]);
      maxi = i; maxj = j;
    }
  } while (i != is || j != js);
  return sqrt(maxd); /* farthest pair is (maxi, maxj). */
}

vector<point> convex_cut(const vector<point> P, const segment& l) {
  vector<point> Q;
  for (int i = 0; i < P.size(); ++i) {
    point A = curr(P, i), B = next(P, i);
    if (ccw(l[0], l[1], A) != -1) Q.push_back(A);
    if (ccw(l[0], l[1], A)*ccw(l[0], l[1], B) < 0)
      Q.push_back(crosspointSS(segment(A, B), l));
  }
  return Q;
}

point max_circle_size_in_polygon_check(double mid, vector<point> &v){
	ll n = v.size();
	vector<point> now(v);
	REP(i, n){
		auto a = v[i];
		auto b = v[(i+1)%n];
		auto vec = b - a;
		vec /= abs(vec);
		vec *= mid;
		vec = vec * point(0, 1);
		segment seg = segment(a + vec, b + vec);
		now = convex_cut(now, seg);
	}
	return (now.empty() ? point(INF, INF): now[0]);
}

// 凸多角形に入る最大の円
circle max_circle_size_in_polygon(vector<point> &v){
	double l = 0;
	double r = convex_diameter(v);
	point ret;
	REP(_, 1000){
		if(abs(l - r) < EPS)break;
		double mid = (l + r) / 2;
		ret = max_circle_size_in_polygon_check(mid, v);
		if(!eq(ret, point(INF, INF)))l = mid;
		else r = mid;
	}
	return circle(ret, l);
}

//　三角形の外接円
circle circumscribed_circle(vector<point> p) {
	segment seg_a = segment((p[1] + p[0]) * 0.5,
	(p[1] + p[0]) * 0.5 + (p[1] - p[0]) * point(0, 1));
	segment seg_b = segment((p[2] + p[1]) * 0.5,
	(p[2] + p[1]) * 0.5 + (p[2] - p[1]) * point(0, 1));
	circle ret;
	ret.p = crosspointSS(seg_a, seg_b);
	ret.r = distancePP(p[0], ret.p);
	return ret;
}

// ################################### 3D ####################################

struct quaternion;
quaternion conj(quaternion q);
struct point3d {
	double x, y, z;
	point3d():x(0), y(0), z(0){}
	point3d(const point3d &p):x(p.x), y(p.y), z(p.z){}
	point3d(const quaternion &q); // 先行宣言
	point3d(double x_, double y_, double z_):x(x_), y(y_), z(z_){}

	point3d& operator+=(point3d a){x += a.x;y += a.y;z += a.z;return *this;}
	point3d& operator-=(point3d a){x -= a.x;y -= a.y;z -= a.z;return *this;}
	point3d& operator*=(quaternion q); // 先行宣言
	point3d& operator*=(double a){x *= a;y *= a;z *= a;return *this;}
	point3d& operator/=(double a){x /= a;y /= a;z /= a;return *this;}
	point3d operator+(point3d a) const{return point3d(x, y, z)+=a;}
	point3d operator-(point3d a) const{return point3d(x, y, z)-=a;}
	point3d operator-() const{return point3d(-x, -y, -z);}
	point3d operator*(quaternion q); // 先行宣言
	point3d operator*(double a) const{return point3d(x, y, z)*=a;}
	point3d operator/(double a) const{return point3d(x, y, z)/=a;}
	bool operator<(point3d a) const{
		return (x != a.x ? x < a.x : (y != a.y ? y < a.y : z < a.z));}
};

template <class T>
point3d operator*(const T a, const point3d p){return p * a;}

struct segment3d: public array<point3d, 2> {
	segment3d(const point3d &a, const point3d &b) {
		at(0) = a;
		at(1) = b;
	}
};

double abs(point3d p) {	return sqrt(p.x * p.x + p.y * p.y + p.z * p.z); }
double norm(point3d p) {	return p.x * p.x + p.y * p.y + p.z * p.z; }
double dot(point3d a, point3d b){	return a.x * b.x + a.y * b.y + a.z * b.z; }
point3d cross(point3d a, point3d b){
	return point3d(a.y * b.z - a.z * b.y,
								 a.z * b.x - a.x * b.z,
							   a.x * b.y - a.y * b.x);
}

point3d projection(const segment3d &l, const point3d &p) {
	double t = dot(p - l[0], l[0] - l[1]) / norm(l[0] - l[1]);
	return l[0] + t*(l[0] - l[1]);
}
point3d reflection(const segment3d &l, const point3d &p) {
	return p + 2. * (projection(l, p) - p);
}

bool intersect3dSP(const segment3d &s, const point3d &p) {
	auto a = s[0] - p;
	auto b = s[1] - p;
	return (abs(cross(a, b)) < EPS && dot(a, b) <= EPS); // triangle inequality
}

bool intersect3dLP(const segment3d &l, const point3d &p) {
	return abs(cross(l[1] - p, l[0] - p)) < EPS;
}

double angle(point3d a, point3d b){
	double tmp = dot(a, b) / (abs(a) * abs(b));
	if(tmp < -1)tmp = -1;
	if(tmp > 1)tmp = 1;
	return acos(tmp);
}

struct plane {
	double a, b, c, d;
	plane():a(0), b(0), c(0), d(0){}
	plane(double a_, double b_, double c_, double d_):a(a_), b(b_), c(c_), d(d_){}
	plane(point3d p1, point3d p2, point3d p3){
		point3d A = p2 - p1;
		point3d B = p3 - p1;
		point3d p = cross(A, B);
		a = p.x;b = p.y;c = p.z;
		d = -(a * p1.x + b * p1.y + c * p1.z);
	}
	double assignment(point3d p){
		return a * p.x + b * p.y + c * p.z + d;
	}
};

double distance(point3d p, plane pl){
	double a = abs(p.x * pl.a + p.y * pl.b + p.z * pl.c + pl.d);
	double b = sqrt(pl.a * pl.a + pl.b * pl.b + pl.c * pl.c);
	return a / b;
}

double distance(plane p, point3d pl){
	return distance(pl, p);
}

point3d projection(point3d p, plane pl){
	double d = distance(p, pl);
	point3d a = point3d(pl.a, pl.b, pl.c);a /= abs(a);
	point3d ret = p + a * d;
	if(distance(ret, pl) < EPS)return ret;
	return p - a * d;
}

point3d crossPoint3d(segment3d s, plane p){
	double bunsi = p.a * s[0].x + p.b * s[0].y + p.c * s[0].z + p.d;
	double bunbo = p.a * (s[0].x - s[1].x) +
								 p.b * (s[0].y - s[1].y) +
								 p.c * (s[0].z - s[1].z);
	if(abs(bunbo) < EPS)return point3d(INF, INF, INF);
	double t = bunsi / bunbo;
	return s[0] + (s[1] - s[0]) * t;
}

struct quaternion {
	double x, y, z, w;
	quaternion():x(0), y(0), z(0){}
	quaternion(const point3d &p):x(p.x), y(p.y), z(p.z), w(0){}
	quaternion(double x_, double y_, double z_, double w_):x(x_), y(y_), z(z_), w(w_){}
	// ベクトルpを軸にrad回転させる
	quaternion(const point3d &p, double rad){
		assert(abs(p) > EPS);
		point3d np(p);np /= abs(np);
		x = np.x * sin(rad / 2);
		y = np.y * sin(rad / 2);
		z = np.z * sin(rad / 2);
		w = cos(rad / 2);
	}
	quaternion& operator*=(double a){x *= a;y *= a;z *= a;w *= a;return *this;}
	quaternion& operator/=(double a){x /= a;y /= a;z /= a;w /= a;return *this;}
	quaternion& operator*=(quaternion q){
		double xx = w * q.x + x * q.w - y * q.z + z * q.y;
		double yy = w * q.y + x * q.z + y * q.w - z * q.x;
		double zz = w * q.z - x * q.y + y * q.x + z * q.w;
		double ww = w * q.w - x * q.x - y * q.y - z * q.z;
		*this = quaternion(xx, yy, zz, ww);return *this;
	}
	quaternion operator*(quaternion q) const{return quaternion(x, y, z, w)*=q;}
	quaternion operator*(double a) const{return quaternion(x, y, z, w)*=a;}
	quaternion operator/(double a) const{return quaternion(x, y, z, w)/=a;}
};

quaternion conj(quaternion q) {
	 return quaternion(-q.x, -q.y, -q.z, q.w);
 }
double abs(quaternion q) {
	return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}
quaternion normalization(quaternion q){
	return q / abs(q);
}

point3d::point3d(const quaternion &q):x(q.x), y(q.y), z(q.z){}
point3d& point3d::operator*=(quaternion q){
	normalization(q);
	*this = point3d(q * quaternion(*this) * conj(q));
	return *this;
}
point3d point3d::operator*(quaternion q){ return point3d(x, y, z)*= q; }

// vecへ平行移動
void translation(vector<point3d> &p, point3d vec){
	REP(i, p.size())p[i] += vec;
}

void scale(vector<point3d> &p, double s){
	REP(i, p.size())p[i] *= s;
}

// pをaxisを軸にaからbまで回転する
void RotateWithAngleAxis(vector<point3d> &p, segment3d axis, point3d a, point3d b) {
	point3d tmp = axis[0];
	translation(p, -tmp);
	axis[0] -= tmp;axis[1] -= tmp;
	a -= tmp;b -= tmp;

	point3d avec = a - projection(axis, a);
	point3d bvec = b - projection(axis, b);
	if(abs(avec) < EPS || abs(bvec) < EPS){

	}
	else if(eq(abs(cross(avec, bvec)), 0)){
		quaternion q = quaternion(axis[1], angle(avec, bvec));
		REP(i, p.size())p[i] *= q;
	}
	else{
		quaternion q = quaternion(cross(bvec, avec), angle(avec, bvec));
		REP(i, p.size())p[i] *= q;
	}

	translation(p, tmp);
	axis[0] += tmp;axis[1] += tmp;
	a += tmp;b += tmp;
}

// ################################### 3D ####################################
// ################################### IO ####################################

istream& operator>>(std::istream& is, point3d& p){
	is >> p.x >> p.y >> p.z;
	return is;
}

ostream& operator<<(ostream& os, const point3d& p){
	os << p.x << " " << p.y << " " << p.z;
	return os;
}

ostream& operator<<(ostream& os, const quaternion& q){
	os << q.x << " " << q.y << " " << q.z << " " << q.w;
	return os;
}

ostream& operator<<(ostream& os, const plane& p){
	os << p.a << "x + " << p.b << "y + " << p.c << "z + " << p.d;
	return os;
}

istream& operator>>(std::istream& is, point& p){
	is >> p.x >> p.y;
  return is;
}

ostream& operator<<(ostream& os, const point& p){
	os << p.x << " " << p.y;
	return os;
}

// ################################### IO ####################################

int main(){
	cin.tie(0);cout.tie(0);ios::sync_with_stdio(false);

	return 0;
}
