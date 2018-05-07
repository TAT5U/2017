using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CharaManager : MonoBehaviour 
{
	private string[] japaneseCharaStrings_ = 
	{
		"あ", "い", "う", "え", "お",
		"か", "き", "く", "け", "こ",
		"さ", "し", "す", "せ", "そ",
		"た", "ち", "つ", "て", "と",
		"な", "に", "ぬ", "ね", "の",
		"は", "ひ", "ふ", "へ", "ほ",
		"ま", "み", "む", "め", "も",
		"や", "ゆ", "よ", ""  , "",
		"ら", "り", "る", "れ", "ろ",
		"わ", "を", "ん", ""  , "消"
	};

	// 番号順に生成
	private void Start()
	{
		string parentName = transform.parent.name.Replace("charaStaringImage", "");
		GetComponent<Text>().text = japaneseCharaStrings_[int.Parse(parentName.ToString())];
	}
}
