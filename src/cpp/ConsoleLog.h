// ConsoleLog.h
//
// Copyright(C) 2020 neobits (Angelo Moro)
//
// This file is part of dev-utils.
//
// dev-utils is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// dev-utils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Foobar.If not, see < https://www.gnu.org/licenses/>.

#pragma once

#ifndef _CONSOLE_LOG_H_
#define _CONSOLE_LOG_H_

#include <string>


namespace Utils
{
	// Console debug log.
	//
	// Based on Open Frameworks ofLog
	// Class idea from http://www.gamedev.net/community/forums/topic.asp?topic_id=525405&whichpage=1&#3406418
	// How to catch std::endl (which is actually a func pointer) http://yvan.seth.id.au/Entries/Technology/Code/std__endl.html

	class ConsoleLog
	{
	public:
		enum EMessageKind {
			Notice,
			Warning,
			Error,
		};

		ConsoleLog(){}

		ConsoleLog(std::string module, EMessageKind kind) {
			msgKind = kind;
			this->module = module;
		}
		virtual ~ConsoleLog() {}

		/// \brief Define flexible stream operator.
		///
		/// This allows the class to use the << std::ostream to read data of
		/// almost any type.
		///
		/// \tparam T the data type to be streamed.
		/// \param value the data to be streamed.
		/// \returns A reference to itself.
		template <class T>
		ConsoleLog& operator<<(const T& value) {
			this->message << value << getPadding();
			level++;
			return *this;
		}

		/// \brief Define flexible stream operator.
		///
		/// This allows the class to use the << std::ostream to catch function
		/// pointers such as std::endl and std::hex.
		///
		/// \param func A function pointer that takes a std::ostream as an argument.
		/// \returns A reference to itself.
		ConsoleLog& operator<<(std::ostream& (*func)(std::ostream&)) {
			func(message);
			DisplayLog(false);
			return *this;
		}

	protected:
		std::string module;    ///< The destination module for this message.
		EMessageKind msgKind;
		std::stringstream message;	///< Temporary buffer.
		
		int level;

		inline void DisplayLog(bool addBreakLine = true)
		{
			std::string prefix;
			switch (msgKind)
			{
			default:
			case EMessageKind::Notice:
				prefix = "[notice]";
				break;
			case EMessageKind::Warning:
				prefix = "[warning]";
				break;
			case EMessageKind::Error:
				prefix = "[error]";
				break;
			}
			std::cout << prefix << " " << this->module << " | "
				<< this->message.str() << (addBreakLine ? "\n" : "");
		}

		///< The padding between std::ostream calls
		inline std::string & getPadding() {
			static std::string * padding = new std::string;
			return *padding;
		}
	};

	class LogNotice : public ConsoleLog
	{
	public:
		LogNotice(std::string module, 
				  EMessageKind kind = EMessageKind::Notice) 
		{
			level = 0;
			msgKind = kind;
			this->module = module;
		}
		virtual ~LogNotice() {}
	};

	class LogError : public ConsoleLog
	{
	public:
		LogError(std::string module, EMessageKind kind = EMessageKind::Error) {
			this->module = module;
			this->msgKind = kind;
		}
		virtual ~LogError() {}
	};

	class LogWarning : public ConsoleLog
	{
	public:
		LogWarning(std::string module, EMessageKind kind = EMessageKind::Error) {
			this->module = module;
			this->msgKind = kind;
		}
		virtual ~LogWarning() {}
	};
}
#endif // !_CONSOLE_LOG_H_