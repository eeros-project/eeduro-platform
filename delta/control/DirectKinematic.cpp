#include "DirectKinematic.hpp"
#include <eeros/math/Matrix.hpp>
#include <eeros/core/EEROSException.hpp>

using namespace eeduro::delta;
using namespace eeros::math;
using namespace eeros;

DirectKinematic::DirectKinematic(Kinematic& kin) : kinematic(kin) { }

void DirectKinematic::run() {
	Vector3 q012, xyz;
	AxisVector xyzp;
	
	q012 = in.getSignal().getValue().getSubMatrix<3, 1>(0, 0);
	
	if(!kinematic.forward(q012, xyz)) throw EEROSException("Calculation of forward kinematic failed!");
	
	xyzp[0] = xyz[0];
	xyzp[1] = xyz[1];
	xyzp[2] = xyz[2];
	xyzp[3] = in.getSignal().getValue()[3];
	
	out.getSignal().setValue(xyzp);
	out.getSignal().setTimestamp(in.getSignal().getTimestamp());
}
