
package exercise4.service;

import java.util.List;
import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;
import javax.xml.bind.annotation.XmlSeeAlso;
import javax.xml.datatype.XMLGregorianCalendar;
import javax.xml.ws.Action;
import javax.xml.ws.RequestWrapper;
import javax.xml.ws.ResponseWrapper;


/**
 * This class was generated by the JAX-WS RI.
 * JAX-WS RI 2.2.7-b01 
 * Generated source version: 2.2
 * 
 */
@WebService(name = "MyWebService", targetNamespace = "http://www.service.com")
@XmlSeeAlso({
    ObjectFactory.class
})
public interface MyWebService {


    /**
     * 
     * @param arg1
     * @param arg0
     * @return
     *     returns boolean
     */
    @WebMethod
    @WebResult(targetNamespace = "")
    @RequestWrapper(localName = "addItem", targetNamespace = "http://www.service.com", className = "exercise4.service.AddItem")
    @ResponseWrapper(localName = "addItemResponse", targetNamespace = "http://www.service.com", className = "exercise4.service.AddItemResponse")
    @Action(input = "http://www.service.com/MyWebService/addItemRequest", output = "http://www.service.com/MyWebService/addItemResponse")
    public boolean addItem(
        @WebParam(name = "arg0", targetNamespace = "")
        String arg0,
        @WebParam(name = "arg1", targetNamespace = "")
        ToDoList arg1);

    /**
     * 
     * @param arg0
     * @return
     *     returns boolean
     */
    @WebMethod
    @WebResult(targetNamespace = "")
    @RequestWrapper(localName = "userRegister", targetNamespace = "http://www.service.com", className = "exercise4.service.UserRegister")
    @ResponseWrapper(localName = "userRegisterResponse", targetNamespace = "http://www.service.com", className = "exercise4.service.UserRegisterResponse")
    @Action(input = "http://www.service.com/MyWebService/userRegisterRequest", output = "http://www.service.com/MyWebService/userRegisterResponse")
    public boolean userRegister(
        @WebParam(name = "arg0", targetNamespace = "")
        User arg0);

    /**
     * 
     * @param arg1
     * @param arg0
     * @return
     *     returns boolean
     */
    @WebMethod
    @WebResult(targetNamespace = "")
    @RequestWrapper(localName = "deleteItem", targetNamespace = "http://www.service.com", className = "exercise4.service.DeleteItem")
    @ResponseWrapper(localName = "deleteItemResponse", targetNamespace = "http://www.service.com", className = "exercise4.service.DeleteItemResponse")
    @Action(input = "http://www.service.com/MyWebService/deleteItemRequest", output = "http://www.service.com/MyWebService/deleteItemResponse")
    public boolean deleteItem(
        @WebParam(name = "arg0", targetNamespace = "")
        String arg0,
        @WebParam(name = "arg1", targetNamespace = "")
        int arg1);

    /**
     * 
     * @param arg0
     * @return
     *     returns boolean
     */
    @WebMethod
    @WebResult(targetNamespace = "")
    @RequestWrapper(localName = "clearItem", targetNamespace = "http://www.service.com", className = "exercise4.service.ClearItem")
    @ResponseWrapper(localName = "clearItemResponse", targetNamespace = "http://www.service.com", className = "exercise4.service.ClearItemResponse")
    @Action(input = "http://www.service.com/MyWebService/clearItemRequest", output = "http://www.service.com/MyWebService/clearItemResponse")
    public boolean clearItem(
        @WebParam(name = "arg0", targetNamespace = "")
        String arg0);

    /**
     * 
     * @param arg2
     * @param arg1
     * @param arg0
     * @return
     *     returns java.util.List<exercise4.service.ToDoList>
     */
    @WebMethod
    @WebResult(targetNamespace = "")
    @RequestWrapper(localName = "queryItem", targetNamespace = "http://www.service.com", className = "exercise4.service.QueryItem")
    @ResponseWrapper(localName = "queryItemResponse", targetNamespace = "http://www.service.com", className = "exercise4.service.QueryItemResponse")
    @Action(input = "http://www.service.com/MyWebService/queryItemRequest", output = "http://www.service.com/MyWebService/queryItemResponse")
    public List<ToDoList> queryItem(
        @WebParam(name = "arg0", targetNamespace = "")
        String arg0,
        @WebParam(name = "arg1", targetNamespace = "")
        XMLGregorianCalendar arg1,
        @WebParam(name = "arg2", targetNamespace = "")
        XMLGregorianCalendar arg2);

}
