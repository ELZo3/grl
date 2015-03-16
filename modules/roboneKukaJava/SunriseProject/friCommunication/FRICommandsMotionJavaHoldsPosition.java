package friCommunication;

import static com.kuka.roboticsAPI.motionModel.BasicMotions.ptp;

import com.kuka.connectivity.fri.FRIConfiguration;
import com.kuka.connectivity.fri.FRISession;
import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;
import com.kuka.roboticsAPI.controllerModel.Controller;
import com.kuka.roboticsAPI.deviceModel.LBR;

/**
 * Creates a FRI Session.
 */
public class FRICommandsMotionJavaHoldsPosition extends RoboticsAPIApplication
{
    private Controller _lbrController;
    private LBR _lbr;
    private String _hostName;

    @Override
    public void initialize()
    {
        _lbrController = (Controller) getContext().getControllers().toArray()[0];
        _lbr = (LBR) _lbrController.getDevices().toArray()[0];
        // **********************************************************************
        // *** change next line to the FRIClient's IP address                 ***
        // **********************************************************************
        _hostName = "127.0.0.1";
    }

    @Override
    public void run()
    {
        // configure and start FRI session
        FRIConfiguration friConfiguration = FRIConfiguration.createRemoteConfiguration(_lbr, _hostName);
        friConfiguration.setSendPeriodMilliSec(4);
        FRISession friSession = new FRISession(friConfiguration);
		FRIJointOverlay motionOverlay = new FRIJointOverlay(session);
		
		CartesianImpedanceControlMode controlMode = new CartesianImpedanceControlMode();
		controlMode.parametrize(CartDOF.X).setStiffness(1000.0);
		controlMode.parametrize(CartDOF.ALL).setDamping(0.7);
        // move to start pose
        _lbr.move(ptp(Math.toRadians(90), .0, .0, Math.toRadians(90), .0, Math.toRadians(-90), .0));

        // sync move for infinite time with overlay ...
		lbr.move(positionHold(controlMode, -1, TimeUnit.SECONDS).addMotionOverlay(motionOverlay));
        //_lbr.moveAsync(ptp(Math.toRadians(-90), .0, .0, Math.toRadians(90), .0, Math.toRadians(-90), .0));

        // ... blending into sync move with overlay
        _lbr.move(ptp(Math.toRadians(90), .0, .0, Math.toRadians(90), .0, Math.toRadians(-90), .0));

        // done
        friSession.close();
    }

    /**
     * main.
     * 
     * @param args
     *            args
     */
    public static void main(final String[] args)
    {
        final FRICommandsMotionJavaHoldsPosition app = new FRICommandsMotionJavaHoldsPosition();
        app.runApplication();
    }

}
