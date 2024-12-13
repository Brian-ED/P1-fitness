remove_lines_by_suffix ← ⟨
  " Images"
  "image"
  " videos"
  " Instructions"
  " diagram"
⟩

siteBottom ← ⟨
  "Need Help?"
  ""
  "    Help Center"
  "    Email Support"
  "    Live Chat"
  "    Gift Certificates"
  "    Send Us Feedback"
  ""
  "Orders & Shipping"
  ""
  "    Order Status"
  "    Returns/Exchanges"
  "    Shipping Support"
  ""
  "Connect With Us"
  ""
  "Join Our Newsletter"
  "Be the first to receive exciting news, features, and special offers from Bodybuilding.com!"
  ""
  "    Careers"
  "    Terms of Use"
  "    Privacy Policy"
  ""
  "    About Us"
  "    Site Map"
  "    Affiliates"
  ""
  "    Privacy Settings"
  "    Advertise with Us"
  "    Help"
  ""
  "� 2024 Bodybuilding.com. All rights reserved. Bodybuilding.com? and BodySpace� are trademarks of Bodybuilding.com."
  "Always consult with a qualified healthcare professional prior to beginning any diet or exercise program or taking any dietary supplement. The content on our website is for informational and educational purposes only and is not intended as medical advice or to replace a relationship with a qualified healthcare professional."
  "Bodybuilding.com5777 N Meeker Ave, Boise, ID 83713-1520 USA 1-866-236-8417"
⟩
siteTop ← ⟨
  ""
  "Articles"
  "Workout Plans"
  "Community"
  "Bodybuilding.com Logo"
  "Sales &"
  "Specials"
  "Top 50"
  "Products"
  "New &"
  "Trending"
  "United States"
  "Account"
  "Cart"
  ""
  "    Main"
  "    Training"
  "    Exercise Database"
⟩

c ← ((¬-˜⊢×·+`»⊸>)"----------"⊸≢¨)⊸⊔ remove_lines_by_suffix {𝕨⊸(⊣≢-∘≠⊸↑)¨⊸/𝕩}´˜ •FLines "clipboard.txt"

simpleStrip ← ({""‿𝕩‿""}¨names)∾⁼¨ 1⊑[muscleGroups⋄names]‿·←2(("    "⊸∾⁼¨⍉∘>)∘(↑¨)⋈↓¨) siteTop⊸∾⁼¨ ∾⟜siteBottom⁼¨⟨⟨⟩⟩⊸∾⁼⌾⊑ c

descriptionLengths ← "    Type: "{𝕗⊐⟜<˜𝕩↑¨˜≠𝕗}¨simpleStrip

descriptions ← descriptionLengths↑¨simpleStrip
simpleStrip ↓¨˜↩ descriptionLengths

types ← "    Type: "⊸∾⁼¨⊑¨simpleStrip
simpleStrip ↓˜¨↩ 1


"    Main Muscle Worked: "⊸∾⁼¨⊑¨simpleStrip
simpleStrip ↓˜¨↩ 1

haveEquipment ← "    Equipment: "⊸(⊣≡≠⊸↑)¨⊑¨simpleStrip
equipment ← haveEquipment ⊣◶⟨"Unknown"⋄"    Equipment: "⊸∾⁼⊑∘⊢⟩¨simpleStrip
simpleStrip 1⊸↓¨⌾(haveEquipment⊸/)↩

level ← "    Level: "⊸∾⁼¨⊑¨simpleStrip
simpleStrip ↓˜¨↩ 1

simpleStrip ⟨""⟩⊸∾⁼¨↩

rating ← •ParseFloat¨⊸⊢⊑¨simpleStrip
simpleStrip ↓˜¨↩ 1


haveAverage ← "Average"⊸≡¨ ⊑¨simpleStrip
simpleStrip ↓¨˜↩ haveAverage

simpleStrip ⟨""⟩⊸∾⁼¨↩

descriptionLines ← ⌊´∘⊐⟜(12↑¨"Need Help?"‿"Variations: "‿"Alternative ")¨ 12↑¨¨simpleStrip
description ← descriptionLines↑¨simpleStrip
description (1↓·∾(@+10)⊸∾¨)¨↩ # Join descriptions

simpleStrip ↓¨˜↩ descriptionLines

hasVariations ← "Variations: "⊸(⊣≡≠⊸↑)¨⊑¨1↑¨simpleStrip
[variationLineCount⋄variations] ← ⍉> hasVariations ⊣◶⟨0‿""⋄{
  variationLineCount ← +´∧`"Alternative Exercises for "⊸(⊣≢≠⊸↑)¨𝕩
  variationLines ← variationLineCount↑(" "≡1⊸↑)⊸↓⌾⊑ "Variations:"⊸∾⁼⌾⊑𝕩
  variationsLines ← (×∘≠¨(¬-˜⊢×·+`»⊸>)⊸⊔⊢) ∨`∘≠⟜' '⊸/¨variationLines
  variationLineCount⋈2↓∾"\n"⊸∾¨∾variationsLines
}⟩¨ simpleStrip
simpleStrip ↓˜¨↩ variationLineCount

alterPrefixes ← "Alternative Exercises for "⊸∾¨names
hasAlternatives ← alterPrefixes≡¨⊑¨1↑¨simpleStrip

StripAwayNonNames ← ⊢ /˜ ∨´∘¬∘∊⟜('.'∾'0'+↕10)¨ ∧ "Average"⊸≢¨ ∧ "Muscle Targeted: "⊸(⊣≢≠⊸↑)¨ ∧ "Equipment Type: "⊸(⊣≢≠⊸↑)¨

alternativeExercises ← ⟨⟩⁼¨⌾((¬hasAlternatives)⊸/) alterPrefixes (StripAwayNonNames¨<⊸(∾⁼)¨)⌾(hasAlternatives⊸/)simpleStrip

alternativeExercises (⍉∘>⊢∾¨·⥊⟜⟨"-"⟩¨·⌈´⊸-≠¨)↩

"out.txt" •FLines ∨`⌾⌽∘≠⟜' '⊸/¨ " | "⊸(<⊣∾⁼·∾∾⚇1)˘ ⍉ (⊢↑˜¨·⌈´≠¨)˘ ∾¨(@+10)⊸=◶⋈‿"\n"¨¨ (∨`∧∨⟜«)∘≠⟜' '⊸/¨ [names⋄muscleGroups⋄equipment⋄types⋄level⋄rating]∾alternativeExercises∾[description]
