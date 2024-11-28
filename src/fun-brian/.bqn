outFile ← "output/main.c"
defaultFile ← "bqn-default-output.c"
saveFile ← "save_data"

type‿elm ← {
  data ← ⟨8⋄64‿'f'⟩•bit._Cast 256⊸|⌾(128⊸+)@-˜•FBytes saveFile
  (⊑¨⋈1⊸↓¨) (¯1↑˜0=≠)⊸∾¨ ∾⟜∞⁼¨+`⊸-∘=⟜∞⊸⊔ data
}

outFile •FChars⟜•FChars⍟(¬•file.Exists∘⊣) defaultFile
cFChr ← •FChars outFile

{
  fmt←⟨
    "txywh" # buttons
    "txy"   # titles
    "" # index -1 is the invalid index
  ⟩

  seach_terms ← ∾⟜"*/"¨ "/*"⊸∾¨ ∾(type⊏fmt)∾⟜•Repr¨¨<¨↕≠elm
  amounts‿spots ← (≠¨⋈∾) /∘⍷⟜cFChr¨seach_terms

  # Time for text replace!!
  flChars ← "eE.¯-π∞"∾'0'+↕10
  newCCode ← {(amounts/•Repr¨∾elm)∾¨˜ ∨`⌾⌽∘¬∘∊⟜flChars⊸/¨ 𝕩}⌾(spots⍋⊸⊏¯1↓(+` cFchr≠⊸↑/⁼spots)⊸⊔) cFchr
  outFile •FChars newCCode
}
# Add the following automatically after (the first?) DrawNewFrame() automatically when button added. (Think about which index the new button should take. Maybe the data file is always saved? the data file should really be integrated into the c file through those label comments huh.) # DrawButton("Type your\nHalliluja", 0.1/*t4*/, InArea(AtPos(0.5/*x4*/, 0.2/*y4*/), WithSize(0.6/*w4*/, 0.2/*h4*/)));
# Multiple files could be one tab. (Multiple tabs in one file?... no...). Have tabs be a menu in the editor.
# Number the buttons/titles/ui-elms in the editor to be same as in file.
# Never replace id of a ui-elm, replacement can overwrite other things.
# Should keep currect amount of ui elements somewhere. Prob just prefix in the save_data file.


# Old code for reading the floats from a c file
  #homeName ← ∾('/'⊐˜»∘«){𝔽⊸(↑⋈𝔽⊸↑∘↓)}•path
  #⟨ToNums⟩←•Import homeName •file.At "bqn-libs/strings.bqn"
  # floatsAtSpots ← ⥊(¬·∧`⌾⌽˘˘floatChars∊˜⊢)⊸({' '¨⌾(𝕨⊸/)𝕩}˘˘)⌽˘˘cFChr⊏˜spots-⌜1+↕20
  # floatsAtSpots ({"Some floats invalid"!𝕩≠⊸≡×´𝕨}⊢⥊)⟜ToNums˜↩≢spots
  # changed ← floatsAtSpots≠1↓𝕗
