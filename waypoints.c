typedef struct
{
  float x;    // x-coordinate
  float y;    // y-coordinate
  float yaw;  // orientation
} Vec2;

const int N = 5; // the maximum number of waypoints
float waypoints[N][2] =
 { {0,      0},
   {-1.0,   -1.0},
   { 1.0,    1.0},
   {-0.5,    1.0},
   {0.2,     0.3}
   };

void rotate( float angle_of_rotation );
void go_straight( float dist );
float waypoint_onestep( Vec2 A, Vec2 B );

task main()
{
	Vec2 A, B;				// A and B denote the starting and ending point of each segment, respectively
  A.yaw = PI / 2.0; // the robot's original orientation w.r.t. the positive x-axis (assumed to be 90 degree)

  // loop through each segment
  for( int i = 0; i < N-1; i ++ )
  {
	  // get the starting point of each segment
    A.x = waypoints[i][0];
	  A.y = waypoints[i][1];

    // get the ending point of each segment
	  B.x = waypoints[i+1][0];
	  B.y = waypoints[i+1][1];

    A.yaw = waypoint_onestep(A, B);
  }
}

// inputs: A stands for the starting point and B stands for the ending point
// A contains its position (A.x and A.y) and orientation (A.yaw)
// B contains its position only (B.x and B.y)
// this function should command the robot to go from position A to position B
// this function should also return the robot's ending orientation (named as angle_at_destination)

// more coding hint: wrap your computed angle_of_rotation to be within [-PI, PI] by:
// if it is greater than PI then minus 2*PI;
// if it is less than -PI then add 2*PI
float waypoint_onestep( Vec2 A, Vec2 B )
{
	// this is the angle (in radians) of a free vector pointing from A to B
	float angle_at_destination = 0;


  return angle_at_destination;
}


// ask the robot to rotate
// the input angle_of_rotation is in radians
// notice that positive angle means to rotate counter-clockwise; negative angle means to rotate clockwise
void rotate( float angle_of_rotation )
{

}

// ask the robot to go straight
// the input dist is in meter
void go_straight( float dist )
{

}
