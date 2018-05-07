using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TransformX : MonoBehaviour {

	// Use this for initialization
	void Start () 
	{
		transform.position = new Vector3(Screen.width / 2, transform.position.y, transform.position.z);
	}
}
