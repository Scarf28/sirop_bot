
void echangerEntiers(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}
 
void ligne(int x1, int y1, int x2, int y2, Uint32 coul)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;
 
  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */
 
    if (y1 > y2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }
 
    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;
 
    setPixelVerif(x, y, coul);
 
    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
	x += xincr;
	d += aincr;
      } else
	d += bincr;
 
      setPixelVerif(x, y, coul);
    }
 
  } else {
    /* parcours par l'axe horizontal */
    
    if (x1 > x2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }
 
    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;
 
    setPixelVerif(x, y, coul);
 
    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
	y += yincr;
	d += aincr;
      } else
	d += bincr;
 
      setPixelVerif(x, y, coul);
    }
  }    
}