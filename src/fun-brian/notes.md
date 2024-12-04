# TODOs, Arbitrary order:
- [*] Store text in the double array between each infinity. Just hope user doesn't type out the infinity representation.

- [ ] Add click-to-switch tab.

- [ ] Add allignment. Probably just snap to grid. Or cross checking other positions?

- [ ] Add Button sticking. When you start dragging a button, don't drag another with you. Plus don't drag 2 at the same time.

- [ ] Resize the interaction area to be within the icon rectnagles.

- [ ] Maybe have 3 different icon dragers, up-down, left-right, all 4.

- [ ] Add the following automatically after (the first?) DrawNewFrame() automatically when button added. (Think about which index the new button should take. Maybe the data file is always saved? the data file should really be integrated into the c file through those label comments huh.) # DrawButton("Type your\nHalliluja", 0.1/*t4*/, InArea(AtPos(0.5/*x4*/, 0.2/*y4*/), WithSize(0.6/*w4*/, 0.2/*h4*/)));

- [ ] Multiple files could be one tab. (Multiple tabs in one file?... no...). Have tabs be a menu in the editor.
- [ ] Number the buttons/titles/ui-elms in the editor to be same as in file.
- [ ] Never replace id of a ui-elm, replacement can overwrite other things.
- [ ] Should keep currect amount of ui elements somewhere. Prob just prefix in the save_data file.
