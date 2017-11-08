// SE VIRA AI PRA ADAPTAR MALUCO
//Calcula o circuncentro de um triangulo
point circumcenter(point p, point q, point r) {
    point a = p-r, b = q-r, c = point(a*(p + r) / 2, b*(q + r) / 2);
    return point(c % point(a.y, b.y), point(a.x, b.x) % c) / (a % b);
}
 
circle spanning_circle(vector<point>& T) {
    int n = T.size();
    random_shuffle(all(T));
    circle C(point(), -INFINITY);
    for (int i = 0; i < n; i++) if (!C.inside(T[i])) {
        C = circle(T[i], 0);
        for (int j = 0; j < i; j++) if (!C.inside(T[j])) {
            C = circle((T[i] + T[j]) / 2, abs(T[i] - T[j]) / 2);
            for (int k = 0; k < j; k++) if (!C.inside(T[k])) {
                point o = circumcenter(T[i], T[j], T[k]);
                C = circle(o, abs(o - T[k]));
            }
        }
    }
    return C;
}
