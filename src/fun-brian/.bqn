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
  newCCode ← {
    (amounts/•Repr¨∾elm)∾¨˜ ∨`⌾⌽∘¬∘∊⟜flChars⊸/¨ 𝕩
  }⌾(spots⍋⊸⊏¯1↓(+` cFchr≠⊸↑/⁼spots)⊸⊔) cFchr

  outFile •FChars newCCode
}

# Old code for reading the floats from a c file
  #homeName ← ∾('/'⊐˜»∘«){𝔽⊸(↑⋈𝔽⊸↑∘↓)}•path
  #⟨ToNums⟩←•Import homeName •file.At "bqn-libs/strings.bqn"
  # floatsAtSpots ← ⥊(¬·∧`⌾⌽˘˘floatChars∊˜⊢)⊸({' '¨⌾(𝕨⊸/)𝕩}˘˘)⌽˘˘cFChr⊏˜spots-⌜1+↕20
  # floatsAtSpots ({"Some floats invalid"!𝕩≠⊸≡×´𝕨}⊢⥊)⟜ToNums˜↩≢spots
  # changed ← floatsAtSpots≠1↓𝕗
