using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour 
{

	// オブジェクトの変数
	public GameObject wallPrefab;

	//間隔
	public float interval;

	public float range = 3.0f;

	// Use this for initialization
	IEnumerator Start () 
	{
		while ( true ) 
		{
			transform.position = new Vector3(transform.position.x,
				Random.Range(-range, range), transform.position.z);
			//インスタンス生成
			Instantiate(wallPrefab, transform.position, transform.rotation);
			
			//設定した間隔
			yield return new WaitForSeconds(interval);	
		}	
	}
	
	// Update is called once per frame
	void Update () 
	{
		
	}
}
