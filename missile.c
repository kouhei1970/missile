//卒業研究C言語学習課題　ミサイルの比例航法による誘導
//初版　2016.5.24
//gitの練習も兼ねてます
//git練習２用の変更行
#include <stdio.h>
#include <math.h>

double integ(double x, double xo, double h, double s);
double differential(double x, double xold, double h);

struct robo {
  double x, y;
  double vx, vy, v;
  double dvx, dvy, dv;
  double theta;
  double angv;
  double dangv;
}


main() {
  struct robo drone[2];
  short i, j;
  short missile=1;
  short airplane=0;
  double h;
  double lambda, dlambda, lambda_old;
  double N;

  lambda = 0.0;
  dlambda = 0.0;
  lambda_old = 0.0;
  N = 3.0;

  //Init
  for (i=0; i<2; i++) {
    drone[i].x = 0.0;
    drone[i].y = 0.0;
    drone[i].vx = 0.0;
    drone[i].vy = 0.0;
    drone[i].v = 0.0;
    drone[i].dv = 0.0;
    drone[i].dvx = 0.0;
    drone[i].dvy = 0.0;
    drone[i].theta = 0.0;
    drone[i].angv = 0.0;
    drone[i].dangv = 0.0;
  }

  drone[missile].x = 1000.0;
  drone[missile].y = 0.0;
  drone[airplane].v = 300.0;
  drone[missile].v = 440.0;
  drone[airplane].theta = M_PI/4.0;
  drone[missile].theta = M_PI;
  drone[airplane].angv = 0.0;//M_PI/2.0;
  drone[missile].angv = 0.0;//3.0*M_PI/2.0;
  h = 0.01;

  for (j = 0; j<1000; j++) {
    if( sqrt((drone[missile].x-drone[airplane].x)*(drone[missile].x-drone[airplane].x) 
          + (drone[missile].y-drone[airplane].y)*(drone[missile].y-drone[airplane].y))<5.0) break;

    for (i=0; i<2; i++) {
      printf("%f %f ",drone[i].x,drone[i].y);

      if(i==missile) {

        lambda=atan2(drone[airplane].y - drone[missile].y, drone[airplane].x - drone[missile].x);
        if(j!=0)dlambda=differential(lambda, lambda_old, h);
        drone[missile].angv=N*dlambda;
        lambda_old=lambda;
      } else {
        drone[airplane].angv=M_PI/10.0;
      }
      drone[i].vx = cos(drone[i].theta)*drone[i].v;
      drone[i].vy = sin(drone[i].theta)*drone[i].v;
      drone[i].x = integ(drone[i].vx,drone[i].dvx,h,drone[i].x);
      drone[i].y = integ(drone[i].vy,drone[i].dvy,h,drone[i].y);
      drone[i].theta = integ(drone[i].angv,drone[i].dangv,h,drone[i].theta);

      drone[i].dvx = drone[i].vx;
      drone[i].dvy = drone[i].vy;
      drone[i].dangv = drone[i].angv;
    }
    printf("\n");
  }
}


double integ(double x, double xold, double h, double s) {
  return s + (x + xold)*h*0.5;
}

double differential(double x, double xold, double h) {
  return (x - xold) / h;
}
