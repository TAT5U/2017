using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResizeSample : MonoBehaviour 
{

	public string[] aa = new string[5];
	void OnValidate()
	{
		if (aa.Length > 5)
		{
			System.Array.Resize(ref aa, 5);
		}
	}
}
