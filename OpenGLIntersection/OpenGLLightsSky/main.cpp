#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

//Vector Math
struct Vec3 {
    float x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3 operator+(const Vec3& v) const { return Vec3(x+v.x, y+v.y, z+v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x-v.x, y-v.y, z-v.z); }
    Vec3 operator*(float s) const { return Vec3(x*s, y*s, z*s); }
    Vec3 operator*(const Vec3& v) const { return Vec3(x*v.x, y*v.y, z*v.z); }
    float dot(const Vec3& v) const { return x*v.x + y*v.y + z*v.z; }
    Vec3 cross(const Vec3& v) const { return Vec3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
    float length() const { return sqrtf(dot(*this)); }
    Vec3 normalize() const { float len=length(); return (len>1e-6f) ? *this*(1.0f/len) : *this; }
    Vec3 reflect(const Vec3& n) const { return *this - n*(2.0f*dot(n)); }
};

float clamp(float v, float lo, float hi) { return std::max(lo, std::min(v, hi)); }

//Data Structures
struct Ray { Vec3 o,d; Ray(const Vec3& o,const Vec3& d):o(o),d(d.normalize()){} };
struct Material { Vec3 color; float reflectivity; };
struct Light { Vec3 pos; Vec3 color; float intensity; };
struct Sphere { Vec3 center; float radius; Material mat; };
struct Plane { Vec3 point,normal; Material mat; };

std::vector<Sphere> spheres;
std::vector<Plane> planes;
std::vector<Light> lights;

void buildScene() {
    planes.push_back({Vec3(0,-1,5), Vec3(0,1,0), {Vec3(0.6f,0.55f,0.45f),0}});
    planes.push_back({Vec3(0,0,8), Vec3(0,0,-1), {Vec3(0.7f,0.65f,0.55f),0}});
    planes.push_back({Vec3(-4,0,5), Vec3(1,0,0), {Vec3(0.65f,0.6f,0.5f),0}});

    struct { float x,y,z,r,g,b; } m[] = {
        {-3.8f,-0.88f,7.8f,0.9f,0.1f,0.1f},{-3.5f,-0.88f,7.8f,0.1f,0.8f,0.2f},
        {-3.8f,-0.88f,7.5f,0.1f,0.3f,0.9f},{-3.5f,-0.88f,7.5f,1.0f,0.8f,0.0f},
        {-3.65f,-0.88f,7.65f,0.8f,0.2f,0.6f},{-3.2f,-0.88f,7.8f,0.2f,0.9f,0.9f},
        {-3.8f,-0.88f,7.2f,0.9f,0.5f,0.0f},{-3.5f,-0.88f,7.2f,0.5f,0.1f,0.5f},
        {-3.75f,-0.66f,7.75f,1.0f,1.0f,1.0f},{-3.55f,-0.66f,7.55f,0.3f,0.3f,0.3f},
        {-3.25f,-0.66f,7.75f,0.9f,0.9f,0.1f},{-3.75f,-0.66f,7.4f,0.1f,0.7f,0.5f},
        {-3.3f,-0.66f,7.6f,0.4f,0.1f,0.7f},{-3.6f,-0.66f,7.3f,0.8f,0.3f,0.3f},
        {-3.7f,-0.66f,7.2f,0.2f,0.6f,0.9f},{-3.65f,-0.44f,7.65f,0.7f,0.8f,0.1f},
        {-3.4f,-0.44f,7.7f,0.3f,0.9f,0.4f},{-3.7f,-0.44f,7.5f,0.9f,0.2f,0.3f},
        {-3.5f,-0.44f,7.35f,0.1f,0.7f,0.8f},{-3.3f,-0.44f,7.45f,0.6f,0.8f,0.1f},
        {-3.6f,-0.22f,7.6f,0.8f,0.5f,0.7f},{-3.45f,-0.22f,7.6f,0.2f,0.2f,0.7f},
        {-3.7f,-0.22f,7.45f,0.5f,0.6f,0.9f},{-3.35f,-0.22f,7.55f,0.3f,0.1f,0.5f},
        {-3.6f,0.0f,7.5f,0.9f,0.8f,0.2f},{-3.5f,0.0f,7.6f,0.4f,0.4f,1.0f},
        {-3.0f,-0.88f,7.3f,0.6f,0.2f,0.2f},{-2.8f,-0.88f,7.7f,0.2f,0.8f,0.7f},
        {-3.2f,-0.88f,7.0f,0.5f,0.5f,0.9f},{-2.2f,-0.88f,7.8f,0.9f,0.4f,0.1f},
        {-3.6f,-0.88f,6.8f,0.7f,0.7f,0.0f},{-3.9f,-0.88f,7.0f,0.3f,0.1f,0.8f},
        {-2.5f,-0.88f,7.2f,0.8f,0.6f,0.4f},{-1.5f,-0.88f,7.6f,0.1f,0.5f,0.9f},
        {-3.3f,-0.88f,6.6f,0.6f,0.3f,0.5f},{-3.8f,-0.88f,6.4f,0.9f,0.9f,0.0f}
    };
    for (auto& d : m)
        spheres.push_back({Vec3(d.x,d.y,d.z), 0.12f, {Vec3(d.r,d.g,d.b), 0.5f}});

    lights.push_back({Vec3(-5,2,4), Vec3(1.0f,0.98f,0.9f), 1.8f});
    lights.push_back({Vec3(1,1,3), Vec3(0.6f,0.7f,0.9f), 0.6f});
}

//Intersection
struct HitInfo { bool hit; float t; Vec3 p,n; Material mat; };

HitInfo intersectSphere(const Ray& r, const Sphere& s) {
    HitInfo h={false,1e30f,Vec3(),Vec3(),Material()};
    Vec3 oc=r.o-s.center;
    float a=r.d.dot(r.d), b=2*oc.dot(r.d), c=oc.dot(oc)-s.radius*s.radius;
    float disc=b*b-4*a*c;
    if (disc>=0) {
        float sq=sqrtf(disc);
        float t0=(-b-sq)/(2*a), t1=(-b+sq)/(2*a);
        float t=(t0>0.001f?t0:(t1>0.001f?t1:-1));
        if (t>0.001f) {
            h.hit=true; h.t=t; h.p=r.o+r.d*t;
            h.n=(h.p-s.center).normalize(); h.mat=s.mat;
        }
    }
    return h;
}

HitInfo intersectPlane(const Ray& r, const Plane& p) {
    HitInfo h={false,1e30f,Vec3(),Vec3(),Material()};
    float denom=r.d.dot(p.normal);
    if (fabs(denom)>1e-6f) {
        float t=(p.point-r.o).dot(p.normal)/denom;
        if (t>0.001f) {
            h.hit=true; h.t=t; h.p=r.o+r.d*t;
            h.n=p.normal; h.mat=p.mat;
        }
    }
    return h;
}

HitInfo intersectScene(const Ray& r) {
    HitInfo closest; float ct=1e30f;
    for (auto& s: spheres){ auto h=intersectSphere(r,s); if (h.hit&&h.t<ct){ct=h.t;closest=h;} }
    for (auto& p: planes)  { auto h=intersectPlane(r,p);   if (h.hit&&h.t<ct){ct=h.t;closest=h;} }
    return closest;
}

//Improved shadow test(avoids false self-shadowing)
bool isInShadow(const Vec3& pt, const Vec3& norm, const Light& light) {
    Vec3 ldir = (light.pos - pt).normalize();
    Vec3 origin = pt + norm * 0.03f + ldir * 0.01f;
    float dist = (light.pos - pt).length();
    Ray sray(origin, ldir);
    for (auto& s : spheres) {
        HitInfo h = intersectSphere(sray, s);
        if (h.hit && h.t < dist) return true;
    }
    return false;
}

//Lighting with specular highlights
Vec3 calcLight(const HitInfo& hit, const Vec3& vdir, int depth) {
    if (depth <= 0) return Vec3(0.12f, 0.12f, 0.12f);
    Vec3 amb(0.2f, 0.2f, 0.2f);
    Vec3 col = amb;

    for (auto& L : lights) {
        Vec3 ldir = (L.pos - hit.p).normalize();
        float dist = (L.pos - hit.p).length();
        float atten = 1.0f / (1.0f + 0.1f * dist + 0.02f * dist * dist);

        if (isInShadow(hit.p, hit.n, L)) continue;

        float NdotL = std::max(0.0f, hit.n.dot(ldir));
        Vec3 diffuse = hit.mat.color * L.color * (NdotL * L.intensity * atten);

        Vec3 R = ldir * -1.0f;
        R = hit.n * (2.0f * R.dot(hit.n)) - R;
        float RdotV = std::max(0.0f, R.dot(vdir));
        Vec3 spec = Vec3(1, 1, 1) * L.color * (powf(RdotV, 64) * L.intensity * atten * 0.6f);

        col = col + diffuse + spec;
    }

    if (hit.mat.reflectivity > 0.01f) {
        Vec3 refl = vdir * -1.0f;
        refl = hit.n * (2.0f * refl.dot(hit.n)) - refl;
        Ray rr(hit.p + refl * 0.01f, refl);
        HitInfo rh = intersectScene(rr);
        if (rh.hit) {
            Vec3 rc = calcLight(rh, refl * -1.0f, depth - 1);
            col = col * (1 - hit.mat.reflectivity) + rc * hit.mat.reflectivity;
        }
    }
    return Vec3(clamp(col.x, 0, 1), clamp(col.y, 0, 1), clamp(col.z, 0, 1));
}

//Rendering
const int W=800, H=600;
unsigned char img[H][W][3];

void render() {
    Vec3 cam(-2.8f,-0.3f,5.2f), look(-3.5f,-0.5f,7.5f), up(0,1,0);
    Vec3 w = (cam-look).normalize();
    Vec3 u = up.cross(w).normalize();
    Vec3 v = w.cross(u);
    float fov=55.0f*3.14159f/180.0f, asp=(float)W/H;

    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            float px = (2*(x+0.5f)/W - 1) * tanf(fov/2) * asp;
            float py = (1 - 2*(y+0.5f)/H) * tanf(fov/2);
            Vec3 dir = (u*px + v*py - w*1.0f).normalize();
            Ray ray(cam, dir);

            HitInfo hit = intersectScene(ray);
            Vec3 col(0.2f,0.15f,0.1f);
            if (hit.hit) col = calcLight(hit, ray.d*-1.0f, 8);

            img[H-1-y][x][0] = (unsigned char)(col.x*255);
            img[H-1-y][x][1] = (unsigned char)(col.y*255);
            img[H-1-y][x][2] = (unsigned char)(col.z*255);
        }
    }
    std::cout << "Rendering done." << std::endl;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, img);
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    buildScene();
    render();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(W, H);
    glutCreateWindow("Marble pile with highlights and shadows");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}