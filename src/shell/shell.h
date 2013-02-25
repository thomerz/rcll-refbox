
/***************************************************************************
 *  shell.h - LLSF RefBox shell
 *
 *  Created: Fri Feb 15 10:12:50 2013
 *  Copyright  2013  Tim Niemueller [www.niemueller.de]
 ****************************************************************************/

/*  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the authors nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __LLSF_REFBOX_SHELL_SHELL_H_
#define __LLSF_REFBOX_SHELL_SHELL_H_

#include <cursesapp.h>

#include <boost/asio.hpp>
#include <google/protobuf/message.h>

#include <map>
#include <vector>
#include <string>

class NCursesPanel;

namespace protobuf_comm {
  class ProtobufStreamClient;
}

namespace llsfrb_shell {
#if 0 /* just to make Emacs auto-indent happy */
}
#endif


class LLSFRefBoxShellMachine;
class LLSFRefBoxShellRobot;

class LLSFRefBoxShell : public NCursesApplication {
 public:
  LLSFRefBoxShell(int argc, char **argv);
  ~LLSFRefBoxShell();

  // return 1 to get title
  int  titlesize() const { return 0; }
  void title();

  const char * error() const;

  int run();

 private: // methods
  void start_timers();
  void handle_timer(const boost::system::error_code& error);
  void handle_blink_timer(const boost::system::error_code& error);
  void handle_reconnect_timer(const boost::system::error_code& error);
  void handle_signal(const boost::system::error_code& error, int signum);

  void client_connected();
  void client_disconnected(const boost::system::error_code &error);
  void client_msg(uint16_t comp_id, uint16_t msg_type,
		  std::shared_ptr<google::protobuf::Message> msg);

 private: // members
  const char *error_;

  NCursesPanel *panel_;

  NCursesPanel *rb_log_;
  NCursesPanel *game_log_;

  NCursesPanel *p_state_;
  NCursesPanel *p_time_;
  NCursesPanel *p_points_;

  std::vector<LLSFRefBoxShellRobot *> robots_;
  std::map<std::string, LLSFRefBoxShellMachine *> machines_;

  boost::asio::io_service      io_service_;
  boost::asio::deadline_timer  timer_;
  boost::asio::deadline_timer  reconnect_timer_;
  bool                         try_reconnect_;
  boost::asio::deadline_timer  blink_timer_;

  protobuf_comm::ProtobufStreamClient *client;
};


} // end of namespace llsfrb

#endif