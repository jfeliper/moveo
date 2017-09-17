

void mueveaX(long gradosX, long velX, long acelX)
{
  if ((gradosX >= -90) && (gradosX <= 90)) {
    motorX.setAcceleration(acelX * factorX);
    motorX.setMaxSpeed(velX * factorX);
    motorX.moveTo(gradosX * factorX);
  }
}

void mueveaY(long gradosY, long velY, long acelY)
{
  if ((gradosY >= -90) && (gradosY <= 90)) {
    motorY.setAcceleration(acelY * factorY);
    motorY.setMaxSpeed(velY * factorY);
    motorY.moveTo(gradosY * factorY);
  }
}

void mueveaZ(long gradosZ, long velZ, long acelZ)
{
  if ((gradosZ >= -90) && (gradosZ <= 90)) {
    motorZ.setAcceleration(acelZ * factorZ);
    motorZ.setMaxSpeed(velZ * factorZ);
    motorZ.moveTo(gradosZ * factorZ);
  }
}

void mueveaE(long gradosE, long velE, long acelE)
{
  if ((gradosE >= -90) && (gradosE <= 90)) {
    motorE.setAcceleration(acelE * factorE);
    motorE.setMaxSpeed(velE * factorE);
    motorE.moveTo(gradosE * factorE);
  }
}

void mueveaQ(long gradosQ, long velQ, long acelQ)
{
  if ((gradosQ >= -90) && (gradosQ <= 90)) {
    motorQ.setAcceleration(acelQ * factorQ);
    motorQ.setMaxSpeed(velQ * factorQ);
    motorQ.moveTo(gradosQ * factorQ);
  }
}

