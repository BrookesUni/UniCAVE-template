//MIT License
//Copyright 2016-Present 
//Ross Tredinnick
//Benny Wysong-Grass
//University of Wisconsin - Madison Virtual Environments Group
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
//to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, 
//sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

using Unity.Netcode;
using UnityEngine;
using Unity.Netcode.Transports.UTP;
using static UnityEngine.GraphicsBuffer;

#if UNITY_EDITOR
using UnityEditor;
#endif


namespace UniCAVE
{
    /// <summary>
    /// Starts the program as either client or server depending on machine
    /// </summary>
    public class NetworkInitialization : MonoBehaviour
    {

        /// <summary>
        /// Time to wait before giving up network connection.
        /// </summary>
        public static int TimeoutWaitTime = Util.GetTimeoutWaitTime();

        /// <summary>
        /// Reference to the Netcode Network Manager.
        /// </summary>
        public NetworkManager networkManager;

        /// <summary>
        /// Name of the head (server) machine.
        /// </summary>
        [SerializeField]
        public MachineName headMachineAsset;

        public string HeadMachine => MachineName.GetMachineName(headMachineAsset);

        /// <summary>
        /// IP address of the head (server) machine.
        /// </summary>
        [Tooltip("This can be overriden at runtime with parameter serverAddress, for example \"serverAddress 192.168.0.100\"")]
        public string serverAddress = "192.168.4.140";

        /// <summary>
        /// IP port to use for the head (server) machine.
        /// </summary>
        [Tooltip("This can be overriden at runtime with parameter serverPort, for example \"serverPort 8421\"")]
        public int serverPort = 7568;

        /// <summary>
        /// Reference to debug information display to show connection status on screen.
        /// </summary>
        private DebugInfo _debugInfo;


        /// <summary>
        /// Singleton instance.
        /// </summary>
        private static GameObject _instance = null;

        /// <summary>
        /// Singleton check: if another instance exists, destroy this one.
        /// </summary>
        private void Awake()
        {
            if (_instance)
            {
                UnityEngine.Object.Destroy(gameObject);
            }
            else
            {
                _instance = gameObject;
            }
        }

        /// <summary>
        /// Starts as client or server.
        /// </summary>
        void Start()
        {
            // See if server address and port were passed on command line, if so, override property values.
            string serverArg = Util.GetArg("serverAddress");
            if (serverArg != null) serverAddress = serverArg;

            string portArg = Util.GetArg("serverPort");
            if (portArg != null) int.TryParse(portArg, out serverPort);

            // Get our machine name.
            string runningMachineName = Util.GetMachineName();
            Debug.Log($"serverAddress = {serverAddress}, serverPort = {serverPort}, headMachine = {HeadMachine}, runningMachine = {runningMachineName}");

            // Load networkManager with server port and address.
            networkManager = GetComponent<NetworkManager>();
            networkManager.GetComponent<UnityTransport>().ConnectionData.ServerListenAddress = serverAddress;
            networkManager.GetComponent<UnityTransport>().ConnectionData.Port = (ushort)serverPort;
            networkManager.GetComponent<UnityTransport>().ConnectionData.Address = serverAddress;

#if !UNITY_EDITOR
            // If we are the head machine and are not forced to be client, start as server, else start as client.
            if ((Util.GetArg("forceClient") == "1") || (Util.GetMachineName() != HeadMachine))
            {
                networkManager.StartClient();
            }
            else
            {
                networkManager.StartServer();
            }
#else
            // If in editor, always start as server.
            networkManager.StartServer();
#endif
            //try
            //{
            //    // There is no need for the UI DEBUGGER to be connected every single time
            //    _debugInfo = GameObject.Find("UI_DEBUGGER").GetComponent<DebugInfo>();
            //}
            //catch {
            //    Debug.Log("UI DEBUGGER not found in the scene");
            //}
        }

        /// <summary>
        /// Updates connection status and causes clients to keep trying to connect to server
        /// until timeout period has passed, then exit.
        /// </summary>
        void Update()
        {
            // If we are supposed to be the server, just wait. 
            if (Util.GetMachineName() == HeadMachine)
            {
                if (_debugInfo != null)
                {
                    _debugInfo.UpdateConnectionStatus(true);
                }
                return;
            }
            
            // If we are not the server, but aren't connected to the server, try to connect.
            if (!networkManager.IsClient)
            {
                networkManager.StartClient();
            }

            // display connection status
            if (_debugInfo != null)
            {
                _debugInfo.UpdateConnectionStatus(networkManager.IsConnectedClient);
            }

            // If timeout has passed and client isn't connected, quit.
            if (Time.time > NetworkInitialization.TimeoutWaitTime && !networkManager.IsConnectedClient)
            {
                Application.Quit();
            }
        }

#if UNITY_EDITOR
        //[CanEditMultipleObjects]
        [CustomEditor(typeof(NetworkInitialization))]
        class Editor : UnityEditor.Editor
        {
            public override void OnInspectorGUI()
            {
                base.OnInspectorGUI();

                NetworkInitialization script = (NetworkInitialization)target;
                

                string head_machine_message = "Machine name match";
                GUIStyle myStyle = new GUIStyle(GUI.skin.label);
                myStyle.fontSize = 12;
                myStyle.fontStyle = FontStyle.Italic;
                myStyle.normal.textColor = Color.green;
                
                string currentMachineName = Util.GetMachineName();
                if (script.headMachineAsset.Name != currentMachineName)
                {
                    head_machine_message = $"Machine name mismatch{script.headMachineAsset.Name} and {currentMachineName}";
                    myStyle.normal.textColor = Color.red;
                    Debug.LogError(head_machine_message);
                    Debug.LogError("Please update machine name to run UniCAVE!");
                }

                EditorGUILayout.LabelField(head_machine_message, myStyle);

                //serializedObject.Update();


                //GUI.enabled = false;
                //EditorGUILayout.PropertyField(serializedObject.FindProperty(nameof(NetworkInitialization.headMachineAsset)));
                //GUI.enabled = true;


                //// Create a custom style for labels



                //serializedObject.ApplyModifiedProperties();

                if (GUI.changed)
                {
                    EditorUtility.SetDirty(target);
                }
            }
        }
#endif
    }
}