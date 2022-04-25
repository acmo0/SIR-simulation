#include <stdio.h>
#include <stdlib.h>

typedef struct Description Description;
struct Description{
	long double Sains;
	long double Incubation;
	long double Infectes;
	long double Immunises;
	long double Morts;
	long double beta;
	long double gamma;
	long double alpha;
	long double mu;
	long double nu;
	long double delta;
	long double epsilon;
};

long double yn(long double y, long double h,long double (*f)(Description d),Description d){
	long double result = y+h*(*f)(d);
	return result;
}
long double N(Description d){
	return d.Sains+d.Incubation+d.Infectes+d.Immunises;
}
long double dS(Description d){
	return d.nu*N(d)-d.beta*d.Sains*d.Infectes-d.mu*d.Sains+d.epsilon*d.Immunises;
}
long double dE(Description d){
	return d.beta*d.Sains*d.Infectes-d.alpha*d.Incubation-d.mu*d.Incubation;
}
long double dI(Description d){
	return d.alpha*d.Incubation - d.delta*d.Infectes - d.gamma*d.Infectes -d.mu*d.Infectes;
}
long double dR(Description d){
	return d.gamma*d.Infectes - d.mu*d.Immunises-d.epsilon*d.Immunises;
}
long double dD(Description d){
	long double morts = d.delta*d.Infectes;
	return morts;
}

void modele(long double sains0,long double incubation0,long double infectes0, long double alpha,long double beta, long double gamma, long double delta, long double epsilon,long double mu, long double nu,long double duree,long double points){
	printf("Sains %Lf\nIncubation :%Lf\ninfectés : %Lf\nalpha : %Lf\nbeta : %Lf\ngamma : %Lf\ndelta %Lf\nmu : %Lf\nnu : %Lf\nduree : %Lf\npoints : %Lf\n",sains0,incubation0,infectes0,alpha,beta,gamma,delta,mu,nu,duree,points);
	Description systeme = {.Sains = sains0,.Incubation = incubation0, .Infectes = infectes0, .Morts = 0,.Immunises = 0, .alpha = alpha,.beta=beta,.gamma=gamma,.delta=delta,.nu = nu,.mu = mu,.epsilon = epsilon};
	long double* S = NULL;
	long double* I = NULL;
	long double* E = NULL;
	long double* Nt = NULL;
	long double* R = NULL;
	long double* D = NULL;
	long double* X = NULL;
	S = malloc(points*sizeof(long double));
	I = malloc(points*sizeof(long double));
	E = malloc(points*sizeof(long double));
	Nt = malloc(points*sizeof(long double));
	R = malloc(points*sizeof(long double));
	D = malloc(points*sizeof(long double));
	X = malloc(points*sizeof(long double));
	
	if (S==NULL||I==NULL||E==NULL||Nt==NULL||R==NULL||D==NULL||X==NULL){
		printf("Erreur d'allocation");
		exit(0);
	}
	S[0] = systeme.Sains;
	I[0] = systeme.Infectes;
	E[0] = systeme.Incubation;
	Nt[0] = N(systeme);
	R[0] = systeme.Immunises;
	D[0] = systeme.Morts;
	X[0] = 0;
	unsigned long i = 0;
	long double sains = 0;
	long double infectes = 0;
	long double incubation = 0;
	long double n = 0;
	long double immunises = 0;
	long double morts = 0;
	long double h = duree/points;
	for(i = 1;i<points;i++){
		sains = yn(systeme.Sains,h,&dS,systeme);
		infectes = yn(systeme.Infectes,h,&dI,systeme);
		incubation = yn(systeme.Incubation,h,&dE,systeme);
		immunises = yn(systeme.Immunises,h,&dR,systeme);
		morts = yn(systeme.Morts,h,&dD,systeme);
		systeme.Sains = sains;
		systeme.Infectes = infectes;
		systeme.Incubation = incubation;
		systeme.Immunises = immunises;
		systeme.Morts = morts;
		S[i] = systeme.Sains;
		I[i] = systeme.Infectes;
		E[i] = systeme.Incubation;
		Nt[i] = N(systeme);
		R[i] = systeme.Immunises;
		D[i] = systeme.Morts;
		X[i] = i*h;
	}
	printf("Simulation finie");
	FILE* output = NULL;
	output = fopen("output.csv","w");
	if(output != NULL){
		int i = 0;
		fprintf(output,"X,Sains,Infectés,Incubation,Population Totale, Réémis, Morts\n");
		for(i = 0;i<points;i=i+10){
			fprintf(output,"%.8Lf,%.8Lf,%.8Lf,%.8Lf,%.8Lf,%.8Lf,%.8Lf\n",X[i],S[i],I[i],E[i],Nt[i],R[i],D[i]);
		}
		fclose(output);
	}else{
		printf("Impossible d'ouvrir le fichier");
	}
}
int main(int argc, char *argv[]){
	if (argc == 1){
		printf("Usage : ./simulation_sir S0 E0 I0 alpha beta gamma delta epsilon mu nu duration points\n\n\nS0 : initial percentage of healthy population\nE0 : initial percentage of exposed pupulation\nI0 initial percentage of infected population\nalpha : incubation rate per time\nbeta : average number of contacts (per person per time)\ngamma : cure rate (per time)\ndelta : death rate (per time)\nepsilon : deimmunization rate (per time)\nmu : natural death rate (per time)\nnu : birth rate (per time)\nduration of simulation (in day)\npoints : number of points for the simulation\n\n\n(see github for more details)");
	}
	if (argc != 13){
		exit(0);
	}
	char *endPtr;
	long double sains = strtold(argv[1],&endPtr);
	long double incubation = strtold(argv[2],&endPtr);
	long double infectes = strtold(argv[3],&endPtr);
	long double alpha = strtold(argv[4],&endPtr);
	long double beta = strtold(argv[5],&endPtr);
	long double gamma = strtold(argv[6],&endPtr);
	long double delta = strtold(argv[7],&endPtr);
	long double epsilon = strtold(argv[8],&endPtr);
	long double mu = strtold(argv[9],&endPtr);
	long double nu = strtold(argv[10],&endPtr);
	long double duree = strtold(argv[11],&endPtr);
	long double points = strtold(argv[12],&endPtr);
	printf("Sains %Lf\nIncubation :%Lf\ninfectés : %Lf\nalpha : %Lf\nbeta : %Lf\ngamma : %Lf\ndelta %Lf\nepsilon %Lf\nmu : %Lf\nnu : %Lf\nduree : %Lf\npoints : %Lf\n",sains,incubation,infectes,alpha,beta,gamma,delta,epsilon,mu,nu,duree,points);
	modele(sains,incubation,infectes,alpha,beta,gamma,delta,epsilon,mu,nu,duree,points);
	system("python3 generate.py");
	return 0;
}
