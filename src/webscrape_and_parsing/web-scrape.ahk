#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

<^>!k::

path := "clipboard.txt"
pathToSites := "links.txt"

Loop, read, %pathToSites%,
{
  Send, ^t
  Send, %A_LoopReadLine%
  Send, {Enter}
  Send, {Shift Up}
  Send, {Ctrl Up}
  Sleep, 3500
  Send, ^a
  Send, ^c
  Sleep, 200
  FileAppend, %Clipboard%, %path%
  FileAppend, ----------, %path%
  Send, ^w
}
return

<^>!r::
Reload
return