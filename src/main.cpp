/*! \mainpage Calendar app
 *  \section Introduction
 *  Calendar app is a user-friendly calendar controlled by simple commands. It supports single and recurring events. Events can have notes about their participants, location and date and time they are happening at
 *  \section Commands
 *  <ul>
 *  <li></li>
 *  Calendar app supports following commands
 *	<li>cancel:						Cancels current action
 *	<li>exit:							Saves events and exits application
 *	<li>create <recurring|single>:		Used to create a new event
 *	<li>draw <""|day|month|next|previous|set|week>:	Draws events
 *	<li>select <all|date|place|title>:	Selects an event
 *	<ul>
 *		<li>delete:					    Deletes an event
 *		<li>info:						Prints out info about event
 *		<li>edit:						Edits an event
 *		<ul>
 *			<li>person:				    Edits people in event
 *			    <ul>
 *				<li>add:				Adds a new person
 *				<li>list:				Shows all people
 *				<li>delete:			    Deletes person
 *			    </ul>
 *			</ul>
 *			<li>location:				Changes location
 *			<li>title:					Changes title
 *			<li>lock:					Disables editing on event
 *			<li>duration:				Changes duration of an event
 *			<li>move:					Moves an event
 *		</ul>
 *	<li>export:						    Exports all commands
 *	<li>import:						    Imports events
 *	</ul>
 */

#include "CalendarApp.h"

int main() {
    CalendarApp app;
    app.start();
    return 0;
}
