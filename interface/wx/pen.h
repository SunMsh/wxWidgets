/////////////////////////////////////////////////////////////////////////////
// Name:        pen.h
// Purpose:     interface of wxPen* classes
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    The possible styles for a wxPen.
*/
enum wxPenStyle
{
    wxPENSTYLE_INVALID = -1,

    wxPENSTYLE_SOLID,
        /**< Solid style. */

    wxPENSTYLE_DOT,
        /**< Dotted style. */

    wxPENSTYLE_LONG_DASH,
        /**< Long dashed style. */

    wxPENSTYLE_SHORT_DASH,
        /**< Short dashed style. */

    wxPENSTYLE_DOT_DASH,
        /**< Dot and dash style. */

    wxPENSTYLE_USER_DASH,
        /**< Use the user dashes: see wxPen::SetDashes. */

    wxPENSTYLE_TRANSPARENT,
        /**< No pen is used. */

    wxPENSTYLE_STIPPLE_MASK_OPAQUE,
        /**< @todo WHAT's this? */

    wxPENSTYLE_STIPPLE_MASK,
        /**< @todo WHAT's this? */

    wxPENSTYLE_STIPPLE,
        /**< Use the stipple bitmap. */

    wxPENSTYLE_BDIAGONAL_HATCH,
        /**< Backward diagonal hatch. */

    wxPENSTYLE_CROSSDIAG_HATCH,
        /**< Cross-diagonal hatch. */

    wxPENSTYLE_FDIAGONAL_HATCH,
        /**< Forward diagonal hatch. */

    wxPENSTYLE_CROSS_HATCH,
        /**< Cross hatch. */

    wxPENSTYLE_HORIZONTAL_HATCH,
        /**< Horizontal hatch. */

    wxPENSTYLE_VERTICAL_HATCH,
        /**< Vertical hatch. */

    wxPENSTYLE_FIRST_HATCH = wxPENSTYLE_BDIAGONAL_HATCH,
    wxPENSTYLE_LAST_HATCH = wxPENSTYLE_VERTICAL_HATCH
};

/**
    The possible join values of a wxPen.

    @todo use wxPENJOIN_ prefix
*/
enum wxPenJoin
{
    wxJOIN_INVALID = -1,

    wxJOIN_BEVEL = 120,
    wxJOIN_MITER,
    wxJOIN_ROUND,
};


/**
    The possible cap values of a wxPen.

    @todo use wxPENCAP_ prefix
*/
enum wxPenCap
{
    wxCAP_INVALID = -1,

    wxCAP_ROUND = 130,
    wxCAP_PROJECTING,
    wxCAP_BUTT
};



/**
    @class wxPen

    A pen is a drawing tool for drawing outlines. It is used for drawing
    lines and painting the outline of rectangles, ellipses, etc.
    It has a colour, a width and a style.

    @note On a monochrome display, wxWidgets shows all non-white pens as black.

    Do not initialize objects on the stack before the program commences,
    since other required structures may not have been set up yet.
    Instead, define global pointers to objects and create them in wxApp::OnInit()
    or when required.

    An application may wish to dynamically create pens with different characteristics,
    and there is the consequent danger that a large number of duplicate pens will
    be created. Therefore an application may wish to get a pointer to a pen by using
    the global list of pens ::wxThePenList, and calling the member function
    wxPenList::FindOrCreatePen().
    See wxPenList for more info.

    This class uses @ref overview_refcount "reference counting and copy-on-write" internally
    so that assignments between two instances of this class are very cheap.
    You can therefore use actual objects instead of pointers without efficiency problems.
    If an instance of this class is changed it will create its own data internally
    so that other instances, which previously shared the data using the reference
    counting, are not affected.

    @library{wxcore}
    @category{gdi}

    @stdobjects
    @li ::wxNullPen
    @li ::wxBLACK_DASHED_PEN
    @li ::wxBLACK_PEN
    @li ::wxBLUE_PEN
    @li ::wxCYAN_PEN
    @li ::wxGREEN_PEN
    @li ::wxGREY_PEN
    @li ::wxLIGHT_GREY_PEN
    @li ::wxMEDIUM_GREY_PEN
    @li ::wxRED_PEN
    @li ::wxTRANSPARENT_PEN
    @li ::wxWHITE_PEN

    @see wxPenList, wxDC, wxDC::SetPen()
*/
class wxPen : public wxGDIObject
{
public:
    /**
        Default constructor. The pen will be uninitialised, and IsOk() will return @false.
    */
    wxPen();

    /**
        Constructs a pen from a colour object, pen width and style.

        @param colour
            A colour object.
        @param width
            Pen width. Under Windows, the pen width cannot be greater than 1 if
            the style is @c wxDOT, @c wxLONG_DASH, @c wxSHORT_DASH, @c wxDOT_DASH, or @c wxUSER_DASH.
        @param style
            The style may be one of the ::wxPenStyle values.

        @remarks Different versions of Windows and different versions of other
                 platforms support very different subsets of the styles above
                 - there is no similarity even between Windows95 and Windows98 -
                 so handle with care.

        @see SetStyle(), SetColour(), SetWidth()
    */
    wxPen(const wxColour& colour, int width = 1, wxPenStyle style = wxPENSTYLE_SOLID);

    /**
        Constructs a stippled pen from a stipple bitmap and a width.

        @param width
            Pen width. Under Windows, the pen width cannot be greater than 1 if
            the style is @c wxDOT, @c wxLONG_DASH, @c wxSHORT_DASH, @c wxDOT_DASH, or @c wxUSER_DASH.
        @param stipple
            A stipple bitmap.

        @onlyfor{wxmsw,wxmac}

        @see SetWidth(), SetStipple()
    */
    wxPen(const wxBitmap& stipple, int width);

    /**
        Copy constructor, uses @ref overview_refcount.

        @param pen
            A pointer or reference to a pen to copy.
    */
    wxPen(const wxPen& pen);

    /**
        Destructor.
        @see @ref overview_refcount_destruct "reference-counted object destruction"

        @remarks Although all remaining pens are deleted when the application
                 exits, the application should try to clean up all pens
                 itself. This is because wxWidgets cannot know if a
                 pointer to the pen object is stored in an application
                 data structure, and there is a risk of double deletion.
    */
    virtual ~wxPen();

    /**
        Returns the pen cap style, which may be one of @c wxCAP_ROUND, @c
        wxCAP_PROJECTING and @c wxCAP_BUTT.

        The default is @c wxCAP_ROUND.

        @see SetCap()
    */
    virtual wxPenCap GetCap() const;

    /**
        Returns a reference to the pen colour.

        @see SetColour()
    */
    virtual wxColour GetColour() const;

    /**
        Gets an array of dashes (defined as char in X, DWORD under Windows).
        @a dashes is a pointer to the internal array. Do not deallocate or store this
        pointer.

        @return The number of dashes associated with this pen.

        @see SetDashes()
    */
    virtual int GetDashes(wxDash** dashes) const;

    /**
        Returns the pen join style, which may be one of @c wxJOIN_BEVEL, @c
        wxJOIN_ROUND and @c wxJOIN_MITER.

        The default is @c wxJOIN_ROUND.

        @see SetJoin()
    */
    virtual wxPenJoin GetJoin() const;

    /**
        Gets a pointer to the stipple bitmap.

        @see SetStipple()
    */
    virtual wxBitmap* GetStipple() const;

    /**
        Returns the pen style.

        @see wxPen(), SetStyle()
    */
    virtual wxPenStyle GetStyle() const;

    /**
        Returns the pen width.

        @see SetWidth()
    */
    virtual int GetWidth() const;

    /**
        Returns @true if the pen is initialised.
    */
    virtual bool IsOk() const;

    /**
        Sets the pen cap style, which may be one of @c wxCAP_ROUND, @c wxCAP_PROJECTING
        and @c wxCAP_BUTT. The default is @c wxCAP_ROUND.

        @see GetCap()
    */
    virtual void SetCap(wxPenCap capStyle);

    //@{
    /**
        The pen's colour is changed to the given colour.

        @see GetColour()
    */
    virtual void SetColour(wxColour& colour);
    virtual void SetColour(unsigned char red, unsigned char green, unsigned char blue);
    //@}

    /**
        Associates an array of pointers to dashes (defined as char in X, DWORD under
        Windows) with the pen.

        The array is not deallocated by wxPen, but neither must it be deallocated by
        the calling application until the pen is deleted or this function is called
        with a @NULL array.

        @see GetDashes()
    */
    virtual void SetDashes(int n, const wxDash* dash);

    /**
        Sets the pen join style, which may be one of @c wxJOIN_BEVEL, @c wxJOIN_ROUND
        and @c wxJOIN_MITER.

        The default is @c wxJOIN_ROUND.

        @see GetJoin()
    */
    virtual void SetJoin(wxPenJoin join_style);

    /**
        Sets the bitmap for stippling.

        @see GetStipple()
    */
    virtual void SetStipple(const wxBitmap& stipple);

    /**
        Set the pen style.

        @see wxPen()
    */
    virtual void SetStyle(wxPenStyle style);

    /**
        Sets the pen width.

        @see GetWidth()
    */
    virtual void SetWidth(int width);

    /**
        Inequality operator.

        See @ref overview_refcount_equality "reference-counted object comparison" for
        more info.
    */
    bool operator!=(const wxPen& pen) const;

    /**
        Assignment operator, using @ref overview_refcount.
    */
    wxPen& operator=(const wxPen& pen);

    /**
        Equality operator.

        See @ref overview_refcount_equality "reference-counted object comparison" for
        more info.
    */
    bool operator==(const wxPen& pen) const;
};

/**
    An empty pen.
*/
wxPen wxNullPen;

/**
    Red pen.
*/
wxPen* wxRED_PEN;

/**
    Cyan pen.
*/
wxPen* wxCYAN_PEN;

/**
    Green pen.
*/
wxPen* wxGREEN_PEN;

/**
    Black pen.
*/
wxPen* wxBLACK_PEN;

/**
    White pen.
*/
wxPen* wxWHITE_PEN;

/**
    Transparent pen.
*/
wxPen* wxTRANSPARENT_PEN;

/**
    Black dashed pen.
*/
wxPen* wxBLACK_DASHED_PEN;

/**
    Grey pen.
*/
wxPen* wxGREY_PEN;

/**
    Medium-grey pen.
*/
wxPen* wxMEDIUM_GREY_PEN;

/**
    Light-grey pen.
*/
wxPen* wxLIGHT_GREY_PEN;



/**
    @class wxPenList

    There is only one instance of this class: ::wxThePenList.
    Use this object to search for a previously created pen of the desired
    type and create it if not already found. In some windowing systems,
    the pen may be a scarce resource, so it can pay to reuse old
    resources if possible. When an application finishes, all pens will
    be deleted and their resources freed, eliminating the possibility of
    'memory leaks'. However, it is best not to rely on this automatic
    cleanup because it can lead to double deletion in some circumstances.

    There are two mechanisms in recent versions of wxWidgets which make the
    pen list less useful than it once was. Under Windows, scarce resources
    are cleaned up internally if they are not being used. Also, a referencing
    counting mechanism applied to all GDI objects means that some sharing
    of underlying resources is possible. You don't have to keep track of pointers,
    working out when it is safe delete a pen, because the referencing counting does
    it for you. For example, you can set a pen in a device context, and then
    immediately delete the pen you passed, because the pen is 'copied'.

    So you may find it easier to ignore the pen list, and instead create
    and copy pens as you see fit. If your Windows resource meter suggests
    your application is using too many resources, you can resort to using
    GDI lists to share objects explicitly.

    The only compelling use for the pen list is for wxWidgets to keep
    track of pens in order to clean them up on exit. It is also kept for
    backward compatibility with earlier versions of wxWidgets.

    @library{wxcore}
    @category{gdi}

    @stdobjects
    ::wxThePenList

    @see wxPen
*/
class wxPenList
{
public:
    /**
        Constructor. The application should not construct its own pen list:
        use the object pointer ::wxThePenList.
    */
    wxPenList();

    /**
        Finds a pen with the specified attributes and returns it, else creates a
        new pen, adds it to the pen list, and returns it.

        @param colour
            Colour object.
        @param width
            Width of pen.
        @param style
            Pen style. See ::wxPenStyle for a list of styles.
    */
    wxPen* FindOrCreatePen(const wxColour& colour,
                           int width = 1,
                           wxPenStyle style = wxPENSTYLE_SOLID);
};

/**
    The global list of wxPen objects ready to be re-used (for better performances).
*/
wxPenList* wxThePenList;

