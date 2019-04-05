

#include "gurobi_c++.h"

int main(int argc, char *argv[])
{
	try
	{
		GRBEnv env = GRBEnv();
		GRBModel model = GRBModel(env);

		//setting the constants
		int c = 8;
		int w[] = { 3,8,5 };
		int r[] = { 4,6,5 };
		const int n = sizeof(r)/sizeof(r[0]);

		int i,k;

		// Setting decision variables
		GRBVar x[n];
		for (k = 1; k <= n; k++) {
			x[k] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_INTEGER);
		}		

		model.update();

		//constraint declaration
		GRBLinExpr LHS = 0;
		for (k = 1; k <= n; k++) {			
			LHS += w[k] * x[k];
		}
		model.addConstr(LHS, GRB_LESS_EQUAL, c);

		// Setting objective function		
		GRBLinExpr obj = 0;

		for (k = 1; k <= n; k++) {
			obj += r[k] * x[k];
		}
		model.setObjective(obj, GRB_MAXIMIZE);	

		// Run the optimizion mpdel
		model.optimize();

		std::cout << "Obj:" << model.get(GRB_DoubleAttr_ObjVal) << std::endl;
		for(k=1;k<=n;k++)
			std::cout <<"x"<<k<<"="<< x[k].get(GRB_DoubleAttr_X) <<std::endl;
			

	}
	catch (GRBException e)
	{
		std::cout << "Error code = "
			<< e.getErrorCode()
			<< std::endl;
		std::cout << e.getMessage() << std::endl;
	}
	catch (...)
	{
		std::cout << "Exception during optimization"
			<< std::endl;
	}
	system("pause");
	return 0;
}