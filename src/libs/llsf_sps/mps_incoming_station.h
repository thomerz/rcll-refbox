/*!
* \file mps_deliver.h
* \brief Definitions for Deliver communication
* \author David Masternak
* \version 1.0
*/

#ifndef MPSINCOMINGSTATION_H
#define MPSINCOMINGSTATION_H

#include "mps.h"

/*!
* \class MPSIncomingStation
* \brief Communication between Refbox and Incoming Station
*/
class MPSIncomingStation : public MPS {
 public:
  /*!
   * \fn MPSIncomingStation(char* ip, int port)
   * \brief Constructor
   * \param ip address of mps
   * \param port port for modbus communication
   */
  MPSIncomingStation(const char* ip, int port);
 
  /*!
   * \fn ~MPSIncomingStation()
   * \brief Destructor
   */
  ~MPSIncomingStation();
  
  /*!
   * \fn getCap(int color, int side)
   * \brief send getCap command
   * \param color color of workpiece that have to be provide
   * \param side on which side workpiece have to be provide
   */
  void getCap(int color, int side);

  /*!
   * \fn capReady()
   * \brief receive capReady command
   * \return true if cap is ready and false if not
   */
  bool capReady();

  /*!
   * \fn isEmpty()
   * \brief receive isEmpty command
   * \return value of empty lanes
   */
  int isEmpty();

  /*!
   * \fn setLight(int light, int state);
   * \param light what color
   * \param state on or off
   */
  void setLight(int light, int state);
  
  /*!
   * \fn processQueue()
   * \brief processing the queue
   */
  void processQueue();

 private:
  int lastId;
};

#endif // MPSINCOMINGSTATION_H
