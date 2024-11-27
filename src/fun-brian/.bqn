data ← ⟨8⋄64‿'f'⟩•bit._Cast 256⊸|⌾(128⊸+)@-˜•FBytes "save_data"

buttons‿titles ← ⍉∘>¨ (2∾˜ 1⊸⊑¨)⊸⊔⟜((1⊸↑∾2⊸↓)¨) {1=≠𝕩?𝕩∾¯1;𝕩}¨ ↕∘≠⊸(∾¨) ∾⟜∞⁼¨+`⊸-∘=⟜∞⊸⊔ data

outFile ← "output/main.c"
defaultFile ← "bqn-default-output.c"

outFile •FChars⟜•FChars⍟(¬•file.Exists∘⊣) defaultFile


cFChr ← •FChars outFile

buttons {[i,t,x,y,w,h]_𝕣:
  fmt←"txywh"
  seach_terms ← ∾⟜"*/"¨ "/*"⊸∾¨ fmt∾⌜•Repr¨i
  spots ← seach_terms/∘⍷¨<cFChr
  (("Duplicate comment labels: "∾•Repr)!0=≠)(⥊seach_terms)/˜1<≠¨⥊spots
  (("Lables missing: "∾•Repr)!0=≠)(⥊seach_terms)/˜0=≠¨⥊spots
  spots ⊑¨↩ # Guarenteed to be only one spot left for each search term

  floatChars ← "eE.¯-π∞"∾'0'+↕10
  homeName ← ∾('/'⊐˜»∘«){𝔽⊸(↑⋈𝔽⊸↑∘↓)}•path

  ⟨ToNums⟩←•Import homeName •file.At "bqn-libs/strings.bqn"
  floatsAtSpots ← ⥊(¬·∧`⌾⌽˘˘floatChars∊˜⊢)⊸({' '¨⌾(𝕨⊸/)𝕩}˘˘)⌽˘˘cFChr⊏˜spots-⌜1+↕20
  floatsAtSpots ({"Some floats invalid"!𝕩≠⊸≡×´𝕨}⊢⥊)⟜ToNums˜↩≢spots
  •SHow floatsAtSpots
  •Show 1↓𝕗

  # Time for text replace!!

}

titles {[i,t,x,y]_𝕣:
  fmt←"txy"
#  •Show i  # ⟨ 2 ⟩

}
